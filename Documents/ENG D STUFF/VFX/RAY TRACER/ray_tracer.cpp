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
    ObjFile mesh("joint3.obj");
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

		std::vector<vector3> colours;
		TriangleColour::anti_aliasing(ratio, u,  v, eye, root,  V, N, FV, FN, area, A, RED, sun, myscene, &colours, L, i-1/2.0f, j+1/2.0f, 0);
		
		// 	vector3 s = vector3::vec_add3(L, vector3::vec_scal_mult(-1*i*ratio,u), vector3::vec_scal_mult(-1*j*ratio,v) );
		// 	vector3 d(s.get_x()-eye.get_x(),s.get_y()-eye.get_y(),s.get_z()-eye.get_z());
		// 	d.normalize();
		// 	vector3 RGB = TriangleColour::intersection_colour(d, eye, root,  V, N, FV, FN, area, A, RED, sun, myscene);
		// 	(colours).push_back(RGB);
		
		float R=0, G=0, B=0;
		for (int k=0; k<colours.size(); k++){
			R = R + colours[k].get_x();
			G = G + colours[k].get_y();
			B = B + colours[k].get_z();
		}
		img[x] = R/(float)colours.size();
		img[x+1]=G/(float)colours.size();
		img[x+2]=B/(float)colours.size();
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