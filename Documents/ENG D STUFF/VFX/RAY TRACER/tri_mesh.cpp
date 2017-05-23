#include "tri_mesh.hpp"
#include "Read_Obj.hpp"
#include "search_tree.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>

mesh::mesh(ObjFile input_mesh){
    input_mesh.get_vertices(&vertices);
    input_mesh.get_texture(&textures);
    input_mesh.get_normals(&normals);
    input_mesh.get_face_data(&face_vertices, &face_normals, &face_textures);
    number_of_faces = input_mesh.get_number_of_faces();
    search_tree::leaf_nodes(vertices, face_vertices, number_of_faces, &leaf_nodes);
	search_tree::build_tree(vertices, face_vertices, &leaf_nodes, &root);
}

mesh::~mesh(){
    if(vertices != nullptr){
       delete [] vertices;
    }
    if(normals != nullptr){
        delete [] normals;
    }
    if(textures != nullptr){
        delete[] textures;
    }
    if(face_vertices != nullptr){
        delete[] face_vertices;
    }
   if(face_normals!=nullptr){
       delete [] face_normals;
   }
   if(face_textures!=nullptr){
       delete [] face_normals;
   }
    search_tree::delete_tree(root);
}