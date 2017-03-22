#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "vec3.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "colour.hpp"
#include "readObj.hpp"
#include "search_tree.hpp"

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};
const int PURPLE[]= {255,0,255};
const int YELLOW[]={255,255,0};
const int GREY []={200,200,200};
#define infinity INT_MAX

int main(int argc, char* argv[] ){

	int width, height;
	if(argc>1){
		width = atoi(argv[1]);
		height = atoi(argv[2]);
	}
	else{
		width=1000;
		height=1000;
	}
	
//initial inputs
    ObjFile mesh("joint2.obj");
    float* V = mesh.get_vertices();
    float* N = mesh.get_normals();
    int* FV = mesh.get_faceV();
    int* FN = mesh.get_faceN();
    int F = mesh.get_number_of_faces();

	search_tree* root;
	std::vector<search_tree*> leaf_nodes;
	search_tree::leaf_nodes(V, FV, F, &leaf_nodes);
	search_tree::build_tree(V, FV, leaf_nodes, &root);

    vector3 eye(0,0,-8);
    vector3 lookup(0,1,-8);
    vector3 lookat(0,0,1);
    Light sun(-5,0,-2,1);
    vector3 light = sun.get_position();
    scene myscene(width,height,90,3);
    float d = myscene.get_distance_to_image();


//set up eye coord system
    vector3 w = vector3::vec_add(eye, vector3::vec_scal_mult(-1, lookat));
    w.normalize();
    vector3 u = vector3::crossproduct(lookup, w);
    u.normalize();
    vector3 v = vector3::crossproduct(w,u); 
    vector3 C = vector3::vec_add(eye,vector3::vec_scal_mult(-d,w));     
    float half_width= (float)myscene.get_width()/2.0f, half_height = (float)myscene.get_height()/2.0f;
    vector3 L = vector3::vec_add3(C, vector3::vec_scal_mult(half_width,u), vector3::vec_scal_mult(half_height,v) );
    float ratio = (myscene.get_width())/((float)myscene.get_x_res());

	float* area = new float[F];
	float* A = new float[3*F];

	TriangleColour::phong_areas(FV, FN, N,V, area, A, F);

    unsigned char *img = new unsigned char[3*myscene.get_x_res()*myscene.get_y_res()];
	
	for (int x = 0; x<3*myscene.get_x_res()*myscene.get_y_res(); x+=3){
		int i, j, c1, c2,c3, c_m1, c_m2, c_m3;
		i=(x/(3))%(myscene.get_x_res());
		j=(x/(3))/(myscene.get_x_res());
		vector3 s = C.vector3::vec_add3(L, vector3::vec_scal_mult(-1*i*ratio,u), vector3::vec_scal_mult(-1*j*ratio,v) );
		vector3 d(s.get_x()-eye.get_x(),s.get_y()-eye.get_y(),s.get_z()-eye.get_z());
		d.normalize();

		Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);

		std::vector<float>  output;
		output.clear();
		if(B_root.ray_box_intersection(eye, d)==1){
			search_tree::traverse_tree(root, eye, d, &output);
		}
		float *k=new float[output.size()+1];
		k[0]=-1;
		if (output.size()>1){
			k[0]=output.size();
			for(int g=1; g<output.size()+1;g++){
				k[g] = output[g-1];
			}
		}
		if( (k[0]!=-1)&&(k[0]>0)){
			float* t_values = new float[k[0]];
			int min_value=-1, t_min = infinity, index;
			float t;
			for (int z=1; z<k[0]+1; z++){
				index = k[z];
				c1 = FV[3*index] -1, c2 = FV[3*index+1]-1, c3 = FV[3*index+2] -1 ;
				triangle tri(V[3*c1], V[3*c1+1], V[3*c1+2], V[3*c2], V[3*c2+1], V[3*c2+2], V[3*c3], V[3*c3+1], V[3*c3+2], RED);
				t = tri.ray_triangle_intersection(eye,d);
				t_values[z-1]=t;
			}
			for (int z=0; z<k[0]; z++){
				if ((t_values[z]>0)){
					vector3 xyz = vector3::vec_add( eye , vector3::vec_scal_mult(t_values[z],d));
					if (xyz.get_z()<t_min){
						t_min = xyz.get_z();
						min_value = z;					
					}
				}
			}
			if (min_value == -1){
				img[x]=0;
				img[x+1]=0;
				img[x+2]=0;
			}
			else{
				float R,G,Bc, B,C, P_P1, P_P2, P_P3, semiPerimeter1, semiPerimeter2, semiPerimeter3, alpha1, alpha2, alpha3;
				int m = k[min_value+1], n1, n2, n3,s;
				c_m1 = FV[3*m] -1, c_m2 = FV[3*m+1]-1, c_m3 = FV[3*m+2] -1 ;
				triangle tri(V[3*c_m1], V[3*c_m1+1], V[3*c_m1+2], V[3*c_m2], V[3*c_m2+1], V[3*c_m2+2], V[3*c_m3], V[3*c_m3+1], V[3*c_m3+2],RED);
				t = tri.ray_triangle_intersection(eye,d);

				if(t!=0){
					tri.set_lighting_constants(0.5, 1*255, 0.3, 170);
					vector3 point = vector3::vec_add(eye, vector3::vec_scal_mult(t-0.001f,d));
					vector3 l = sun.get_light_direction(point);
					vector3 normal=tri.get_triangle_normal();  

					std::vector<float> output2;
					output2.clear();
					if(B_root.ray_box_intersection(point, l)==1){	
						search_tree::traverse_tree(root, point, l, &output2);
					}
					float *k2=new float[output2.size()+1];
					k2[0]=-1;
					if (output2.size()>1){
						k2[0]=output2.size();
						for(int g=1; g<output2.size()+1;g++){
							k2[g] = output2[g-1];
						}
					}
					s = TriangleColour::shadows(k2, FV, V, point, l, RED);		
					delete k2;
					vector3 phong_normal = TriangleColour::phong_normal(m, V, N, FV, FN,  area, A, point);

					vector3 RGB = tri.determine_colour(point, l, d, sun, phong_normal, myscene,s);
					R = RGB.get_x();
					G = RGB.get_y();
					Bc = RGB.get_z();
					if (R > 255){
						R=255;
					}
					if (G > 255){
						G=255;
					}
					if (Bc > 255){
						Bc=255;
					}
					img[x] = R;
					img[x+1]=G;
					img[x+2]=Bc;
					delete t_values;
				}
			}
		}
		else{
			img[x]=0;
			img[x+1]=0;
			img[x+2]=0;	
		}
		delete k;
	}

    std::ofstream my_image;
    my_image.open("test.ppm", std::ios::out| std::ios::binary);
    my_image<<"P6 \n" 
    <<myscene.get_x_res()<<" "
    <<myscene.get_y_res()<<"\n"
    <<255<<"\n";
    for (int i=0; i<3*myscene.get_x_res()*myscene.get_y_res(); i++){
        my_image << img[i]; 
    }
    my_image.close();

    delete FV;
    delete FN;
    delete V;
    delete N;
	delete root;
	delete root->faces_in_node;
	delete area;
	delete A;

    return 0;
}