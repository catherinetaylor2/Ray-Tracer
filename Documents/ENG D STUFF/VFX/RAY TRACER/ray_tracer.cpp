//--------------------------------------------------------- RAY-TRACER ----------------------------------------------------------------------------------------------
//CREATED BY CATHERINE TAYLOR
//
//Began Feb 2017

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
#include "Read_Obj.hpp"
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
		width=1920;
		height=1080;
	}

//Input images for texture mapping.
	unsigned char * data, * data2, *data3, *data4;
	int texture_width, texture_height, texture_width2, texture_height2, texture_width3, texture_height3, texture_width4, texture_height4;
	data = readBMP("metal.bmp", &texture_width, &texture_height);
	data2 = readBMP("scene.bmp", &texture_width2, &texture_height2);
	data3 = readBMP("wood.bmp", &texture_width3, &texture_height3);
	data4 = readBMP("texture.bmp", &texture_width4, &texture_height4);
	int texture_data [] = {texture_width2, texture_height2, texture_width, texture_height, texture_width3, texture_height3, texture_width4, texture_height4};
	std::vector<unsigned char*> texture_bmp = {data2, data, data3, data4};

	float* V_s, *N_s, *VT_s;
	int* FV_s, *FN_s, *F_VT_s, F_s;
	search_tree* root_s; 
	std::vector<search_tree*> leaf_nodes_s;

	ObjFile mesh_sphere("sphere3.obj");
	mesh_sphere.get_mesh_data(mesh_sphere, &FV_s, &FN_s, &F_VT_s, &VT_s, &N_s, &V_s, &F_s);

	search_tree::leaf_nodes(V_s, FV_s, F_s, &leaf_nodes_s);
	search_tree::build_tree(V_s, FV_s, &leaf_nodes_s, &root_s);
	std::cout<<"sphere tree built \n";

	float* area_s = new float[F_s];
	float* A_s = new float[3*F_s];
	std::thread t2(TriangleColour::phong_areas, FV_s, FN_s, N_s,V_s, area_s, A_s, F_s);
	t2.join();

	for (int obj_file_input =  1; obj_file_input<2; obj_file_input++){

		float * V , *N, *VT, *V_h, *N_h, *VT_h, *V_sk, *N_sk, *VT_sk;
		int* FV, *FN, *F_VT, F, *FV_h, *FN_h, *F_VT_h, F_h, *FV_sk, *FN_sk, *F_VT_sk, F_sk; 
		std::cout<<"image no "<<obj_file_input<<"\n";
		std::string j;

		if(obj_file_input < 10){
			j = "000"+std::to_string(obj_file_input);
		}
		else if ((obj_file_input>=10)&&(obj_file_input<100)){
			j= "00" + std::to_string(obj_file_input);
		}
		else{
			j= "0" + std::to_string(obj_file_input);
		}

	//initial inputs
		ObjFile mesh1("sword.obj"); //("sword_OBJ_Seq/sword."+j+ ".obj");
		search_tree* root;
		std::vector<search_tree*> leaf_nodes;
		mesh1.get_mesh_data(mesh1, &FV, &FN, &F_VT, &VT, &N, &V, &F);
		search_tree::leaf_nodes(V, FV, F, &leaf_nodes);
		search_tree::build_tree(V, FV, &leaf_nodes, &root);
		std::cout<<"sword tree built \n";

		ObjFile mesh_handle("handle.obj"); //("handle_OBJ_Seq/handle."+j+ ".obj");
		mesh_handle.get_mesh_data(mesh_handle, &FV_h, &FN_h, &F_VT_h, &VT_h, &N_h, &V_h, &F_h);
		search_tree* root_h;
		std::vector<search_tree*> leaf_nodes_h;
		search_tree::leaf_nodes(V_h, FV_h, F_h, &leaf_nodes_h);
		search_tree::build_tree(V_h, FV_h, &leaf_nodes_h, &root_h);
		std::cout<<"handle tree built \n";

		ObjFile mesh_skeleton("skeleton.obj"); //("skeleton_OBJ_Seq/skeleton."+j+ ".obj");
		mesh_skeleton.get_mesh_data(mesh_skeleton, &FV_sk, &FN_sk, &F_VT_sk, &VT_sk, &N_sk, &V_sk, &F_sk);
		search_tree* root_sk;
		std::vector<search_tree*> leaf_nodes_sk;
		search_tree::leaf_nodes(V_sk, FV_sk, F_sk, &leaf_nodes_sk);
		search_tree::build_tree(V_sk, FV_sk, &leaf_nodes_sk, &root_sk);
		std::cout<<"skeleton tree built \n";

		vector3 eye(50,115,-275); 
		vector3 lookup(0,530,-275);
		vector3 lookat(50,100,1);

		Light sun(-500,350,-400,1);  
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
		vector3 L = vector3::vec_add3(C, vector3::vec_scal_mult(-half_width,u), vector3::vec_scal_mult(half_height,v) );
		float ratio = (myscene.get_width())/((float)myscene.get_x_res());
		
		float* area = new float[F];
		float* A = new float[3*F];
		std::thread t1(TriangleColour::phong_areas, FV, FN, N,V, area, A, F);
		t1.join();	

		float *area_h = new float[F_h];
		float *A_h = new float[3*F_h];
		std::thread t3(TriangleColour::phong_areas, FV_h, FN_h, N_h,V_h, area_h, A_h, F_h);
		t3.join();

		float *area_sk =  new float[F_sk];
		float * A_sk = new float[3*F_sk];
		std::thread t4(TriangleColour::phong_areas, FV_sk, FN_sk, N_sk,V_sk, area_sk, A_sk, F_sk);
		t4.join();	

		std::vector<float*> mesh_data_f = {V_s, N_s, VT_s, area_s, A_s,  V, N, VT, area, A, V_h, N_h, VT_h, area_h, A_h, V_sk, N_sk, VT_sk, area_sk, A_sk};
		std::vector<int*> mesh_data_i = { FV_s, FN_s, F_VT_s, FV, FN, F_VT,  FV_h, FN_h, F_VT_h, FV_sk, FN_sk,  F_VT_sk};
		std::vector<search_tree*> root_data = {root_s, root, root_h, root_sk};

		unsigned char *img = new unsigned char[3*myscene.get_x_res()*myscene.get_y_res()];
		for (int x = 0; x<3*myscene.get_x_res()*myscene.get_y_res(); x+=3){
			int i, j;
			i=(x/(3))%(myscene.get_x_res());
			j=(x/(3))/(myscene.get_x_res());

			std::vector<vector3> colours;
			std::vector<vector3> scene_pos = {u, v, eye};
			float current_pos [] = {i-1/2.0f, j+1/2.0f, 0, ratio, (float)i, (float)j} ;
			TriangleColour::anti_aliasing(scene_pos, root_data, mesh_data_f, mesh_data_i, RED, sun, myscene, &colours, L, current_pos, texture_bmp, texture_data);
			
			float R=0, G=0, B=0;
			for (int k=0; k<(signed)colours.size(); k++){
				R = R + colours[k].get_x();
				G = G + colours[k].get_y();
				B = B + colours[k].get_z();
			}
			img[x] = (unsigned char)(R/colours.size());
			img[x+1]=(unsigned char)(G/colours.size());
			img[x+2]= (unsigned char)(B/colours.size());
		}

		std::ofstream image2(j+".bmp", std::ios::out| std::ios::binary);
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

		delete[] img;
		ObjFile::clean_up(V,N, VT, FV, FN, F_VT);
		search_tree::delete_tree(root);
		delete[] area;
		delete[] A;

		ObjFile::clean_up(V_h,N_h, VT_h, FV_h, FN_h, F_VT_h);
		search_tree::delete_tree(root_h);
		delete[] area_h;
		delete[] A_h;

		ObjFile::clean_up(V_sk,N_sk, VT_sk, FV_sk, FN_sk, F_VT_sk);
		search_tree::delete_tree(root_sk);
		delete[] area_sk;
		delete[]  A_sk; 

		std::cout<<"done \n";
	}

	ObjFile::clean_up(V_s,N_s, VT_s, FV_s, FN_s, F_VT_s);
    search_tree::delete_tree(root_s);
	delete[] area_s;
	delete[] A_s;

    return 0;
}