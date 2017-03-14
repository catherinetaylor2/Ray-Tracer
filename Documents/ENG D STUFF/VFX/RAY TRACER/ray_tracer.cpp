#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "readObj.hpp"

using namespace std;

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
    ObjFile mesh("joint.obj");
    float* V = mesh.get_vertices();
    float* N = mesh.get_normals();
    int* FV = mesh.get_faceV();
    int* FN = mesh.get_faceN();
    int F = mesh.get_number_of_faces();

    vector3 eye(0,0,-8);
    vector3 lookup(0,1,-8);
    vector3 lookat(0,0,1);
    Light sun(-5,0,-2,1);
    vector3 light = sun.get_position();
    scene myscene(width,height,90,3);
    float d = myscene.get_distance_to_image();
    
//set up eye coord system
    vector3 w = eye.vec_add(eye, eye.vec_scal_mult(-1, lookat));
    w.normalize();
    vector3 u = w.crossproduct(lookup, w);
    u.normalize();
    vector3 v = w.crossproduct(w,u); 
    vector3 C = w.vec_add(eye,w.vec_scal_mult(-d,w));     
    float half_width= (float)myscene.get_width()/2.0f, half_height = (float)myscene.get_height()/2.0f;
    vector3 L = C.vec_add3(C, C.vec_scal_mult(half_width,u), C.vec_scal_mult(half_height,v) );
    float ratio = (myscene.get_width())/((float)myscene.get_x_res());

   
    unsigned char *img = new unsigned char[3*myscene.get_x_res()*myscene.get_y_res()];
   
    for (int x = 0; x<3*myscene.get_x_res()*myscene.get_y_res(); x+=3){
        int i, j;
        i=(x/(3))%(myscene.get_x_res());
        j=(x/(3))/(myscene.get_x_res());
        vector3 s = C.vec_add3(L, C.vec_scal_mult(-1*i*ratio,u), C.vec_scal_mult(-1*j*ratio,v) );
        vector3 d(s.get_x()-eye.get_x(),s.get_y()-eye.get_y(),s.get_z()-eye.get_z());
        d.normalize();


       float t_min = FLT_MAX, t;
	   float* t_values = new float[F];
       int min_value = -1, c1, c2, c3;

		for (int k=0; k<F; k++){
			c1 = FV[3*k] -1, c2 = FV[3*k+1]-1, c3 = FV[3*k+2] -1 ;
			triangle tri(V[3*c1], V[3*c1+1], V[3*c1+2], V[3*c2], V[3*c2+1], V[3*c2+2], V[3*c3], V[3*c3+1], V[3*c3+2], RED);
			t = tri.ray_triangle_intersection(eye,d);
			t_values[k]=t;		
		}

		for (int k=0; k<F; k++){
			if ((t_values[k]!=0)){
				vector3 xyz = d.vec_add( eye , d.vec_scal_mult(t_values[k],d));
				if (xyz.get_z()<t_min){
					t_min = xyz.get_z();
					min_value = k;					
				}
			}
		}	
			
		if (min_value == -1){
			img[x]=0;
			img[x+1]=0;
			img[x+2]=0;
		}
		else{
			c1 = FV[3*min_value] -1, c2 = FV[3*min_value+1]-1, c3 = FV[3*min_value+2] -1 ;
			triangle tri(V[3*c1], V[3*c1+1], V[3*c1+2], V[3*c2], V[3*c2+1], V[3*c2+2], V[3*c3], V[3*c3+1], V[3*c3+2], RED);
			t = tri.ray_triangle_intersection(eye,d);
			tri.set_lighting_constants(0.7, 0.8*255, 0.3, 400);

			if (t!=0){
				float ss,  alpha1, alpha2, alpha3, area, A,B,C, semiPerimeter, semiPerimeter1, semiPerimeter2,semiPerimeter3, P_P1, P_P2, P_P3, R,G, Bc;
				int s = 1;

				vector3 point = d.vec_add(eye, d.vec_scal_mult(t-0.00001f,d));
			//	vector3 point = tri.barycentric_coords( int_point);
				vector3 l = sun.get_light_direction(point);
				for (int k=0; k<F; k++){
					c1 = FV[3*k] -1, c2 = FV[3*k+1]-1, c3 = FV[3*k+2] -1 ;
					triangle tri2(V[3*c1], V[3*c1+1], V[3*c1+2], V[3*c2], V[3*c2+1], V[3*c2+2], V[3*c3], V[3*c3+1], V[3*c3+2], RED);

					ss = tri2.ray_triangle_intersection( point, l);			
					if ((ss)> 0){
						s = 0;						
					}			
				 } 

				vector3 normal=tri.get_triangle_normal(tri.get_vertex1(), tri.get_vertex2(), tri.get_vertex3());  
				c1 = FV[3*min_value] -1, c2 = FV[3*min_value+1]-1, c3 = FV[3*min_value+2] -1 ;
				vector3 point1(V[3*c1], V[3*c1+1], V[3*c1+2]);
				vector3 point2(V[3*c2], V[3*c2+1], V[3*c2+2]);
				vector3 point3(V[3*c3], V[3*c3+1], V[3*c3+2]);
				A = sqrt(point1.dotproduct(point1.vec_add(point1, point1.vec_scal_mult(-1, point2)),point1.vec_add(point1, point1.vec_scal_mult(-1, point2))));
				B = sqrt(point1.dotproduct(point1.vec_add(point3, point1.vec_scal_mult(-1, point2)),point1.vec_add(point3, point1.vec_scal_mult(-1, point2))));
				C = sqrt(point1.dotproduct(point1.vec_add(point1, point1.vec_scal_mult(-1, point3)),point1.vec_add(point1, point1.vec_scal_mult(-1, point3))));
				P_P1 = sqrt(point1.dotproduct(point1.vec_add(point1, point1.vec_scal_mult(-1, point)),point1.vec_add(point1, point1.vec_scal_mult(-1, point))));
				P_P2= sqrt(point1.dotproduct(point1.vec_add(point, point1.vec_scal_mult(-1, point2)),point1.vec_add(point, point1.vec_scal_mult(-1, point2))));
				P_P3 = sqrt(point1.dotproduct(point1.vec_add(point, point1.vec_scal_mult(-1, point3)),point1.vec_add(point, point1.vec_scal_mult(-1, point3))));

				semiPerimeter = (A+B+C)/2.0f;
				semiPerimeter1 = (P_P3+B+P_P2)/2.0f;
				semiPerimeter2 = (P_P3+C+P_P1)/2.0f;
				semiPerimeter3 = (A+P_P2+P_P1)/2.0f;
				area = sqrt(semiPerimeter*(semiPerimeter - A)*(semiPerimeter- B)*(semiPerimeter -C));
				alpha1 = sqrt(semiPerimeter1*(semiPerimeter1 - B)*(semiPerimeter1- P_P2)*(semiPerimeter1 -P_P3))/area;
				alpha2 = sqrt(semiPerimeter2*(semiPerimeter2 - C)*(semiPerimeter2- P_P1)*(semiPerimeter2 -P_P3))/area;
				alpha3 = sqrt(semiPerimeter3*(semiPerimeter3 - A)*(semiPerimeter3- P_P2)*(semiPerimeter3 -P_P1))/area;
	
				vector3 RGB1 = tri.determine_colour(point1, l, d, sun, normal, myscene,s);
				vector3 RGB2 = tri.determine_colour(point2, l, d, sun, normal, myscene,s);
				vector3 RGB3 = tri.determine_colour(point3, l, d, sun, normal, myscene,s);
				R = RGB1.get_x()*alpha1+RGB2.get_x()*alpha2+RGB3.get_x()*alpha3;
				G = RGB1.get_y()*alpha1+RGB2.get_y()*alpha2+RGB3.get_y()*alpha3;
				Bc = RGB1.get_z()*alpha1+RGB2.get_z()*alpha2+RGB3.get_z()*alpha3;
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
			}
		}
		delete t_values;
	}

    ofstream my_image;
    my_image.open("test.ppm", ios::out| ios::binary);
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



    return 0;
}