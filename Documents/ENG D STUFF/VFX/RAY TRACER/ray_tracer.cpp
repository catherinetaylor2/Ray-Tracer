#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include "vec3.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "colour.hpp"
#include "readObj.hpp"
#include "search_tree.hpp"
#include "BITMAP.hpp"
#include <omp.h> 

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};
const int PURPLE[]= {255,0,255};
const int YELLOW[]={255,255,0};
const int GREY []={200,200,200};
const int SKELETON[] = {250,230,200};
#define infinity FLT_MAX

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
    ObjFile mesh("sphere1.obj");
    float* V = mesh.get_vertices();
	float* VT = mesh.get_texture();
    float* N = mesh.get_normals();
    int* FV = mesh.get_faceV();
    int* FN = mesh.get_faceN();
    int F = mesh.get_number_of_faces();

	search_tree* root;
	std::vector<search_tree*> leaf_nodes;
	search_tree::leaf_nodes(V, FV, F, &leaf_nodes);
	search_tree::build_tree(V, FV, leaf_nodes, &root);
	std::cout<<"tree built \n";

    vector3 eye(0,0,-14);
    vector3 lookup(0,5,-8);
    vector3 lookat(0,0,1);
    Light sun(-5,5,-5,1);
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

	std::thread t1(TriangleColour::phong_areas, FV, FN, N,V, area, A, F);
	t1.join();

    unsigned char *img = new unsigned char[3*myscene.get_x_res()*myscene.get_y_res()];
	for (int x = 0; x<3*myscene.get_x_res()*myscene.get_y_res(); x+=3){
		int i, j;
		i=(x/(3))%(myscene.get_x_res());
		j=(x/(3))/(myscene.get_x_res());

		std::vector<vector3> colours;
		TriangleColour::anti_aliasing(ratio, u,  v, eye, root,  V, N, FV, FN, area, A, PURPLE, sun, myscene, &colours, L, i-1/2.0f, j+1/2.0f, 0);
		
		// 	vector3 s = vector3::vec_add3(L, vector3::vec_scal_mult(-1*i*ratio,u), vector3::vec_scal_mult(-1*j*ratio,v) );
		// 	vector3 d(s.get_x()-eye.get_x(),s.get_y()-eye.get_y(),s.get_z()-eye.get_z());
		// 	d.normalize();
		// std::cout<<"d "<<d.get_x()<<" "<<d.get_y()<<" "<<d.get_z()<<" "<<eye.get_x()<<" "<<eye.get_y()<<" "<<eye.get_z()<<"\n";
		// 	vector3 RGB = TriangleColour::intersection_colour(d, eye, root,  V, N, FV, FN, area, A, GREY, sun, myscene);
		//	(colours).push_back(RGB);
		
		float R=0, G=0, B=0;
		for (int k=0; k<colours.size(); k++){
			R = R+colours[k].get_x();
			G =  G+colours[k].get_y();
			B = B+ colours[k].get_z();
		}

		img[x] = R/colours.size();  
		img[x+1]=G/colours.size();
		img[x+2]= B/colours.size();

		// img[x] = RGB.get_x();  
		// img[x+1]=RGB.get_y();
		// img[x+2]=RGB.get_z();
	}

    // std::ofstream my_image;
    // my_image.open("test.ppm", std::ios::out| std::ios::binary);
    // my_image<<"P6 \n" 
    // <<myscene.get_x_res()<<" "
    // <<myscene.get_y_res()<<"\n"
    // <<255<<"\n";
    // for (int i=0; i<3*myscene.get_x_res()*myscene.get_y_res(); i++){
    //     my_image << img[i]; 
    // }
    // my_image.close();

std::ofstream image2("test.bmp", std::ios::out| std::ios::binary);
BITMAP_File_Header file_header;
BITMAP_Info_Header info_header;
fill_bitmap_headers(&file_header, &info_header,  width, height);
write_bitmap (&file_header, &info_header,&image2);

    for(auto x = height-1; x>=0; x--){
        for (auto y = 0; y < width; y++) {
            for(auto z =2; z>=0; z--){
               image2<<img[x*width*3 + y*3+ z];
            }
        }
    }
	image2.close();

    delete FV;
    delete FN;
	delete VT;
    delete V;
    delete N;
	delete root;
	delete root->faces_in_node;
	delete area;
	delete A;

    return 0;
}