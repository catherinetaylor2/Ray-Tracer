#include <iostream>
#include "search_tree.hpp"

#define infinity FLT_MAX

void search_tree::build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree* root, int previous_faces){

    int k1=0, k2=0, k3=0; 
    float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;

    for(int i =0; i<number_of_faces; i++){
        for(int j=0; j<3; j++){
            if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)]< xmin){
                xmin = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)];
            }
            if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1]< ymin){
                ymin = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1];
            }
            if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2]< zmin){
                zmin = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2];
            }
            if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)]> xmax){
                xmax = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)];
            }
            if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1]> ymax){
                ymax =vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1];
            }
            if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2]> zmax){
                zmax = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2];
            }
        }
    }
    root->parameters[0] = xmin;
    root->parameters[1] = xmax;
    root->parameters[2] = ymin;
    root->parameters[3] = ymax;
    root->parameters[4] = zmin;
    root->parameters[5] = zmax;
//    std::cout<<"xmax "<<xmax<<" "<<xmin<<"\n ";
//     std::cout<<"ymax "<<ymax<<" "<<ymin<<"\n ";
//     std::cout<<"zmin "<<zmax<<" "<<zmin<<"\n ";

    search_tree*L= new search_tree;
    search_tree*R= new search_tree;

    int l=-1, r=-1, number_l=0, number_r=0, is_inside;
    float boundary_line;

    if ((fabs(xmax - xmin)>fabs(ymax-ymin))&&(fabs(xmax - xmin)>fabs(zmax-zmin))){ //x max axis
        boundary_line = (xmax-xmin)/2.0f +xmin;
       // std::cout<<"bx "<<boundary_line<<"\n";
        l=-1, r=-1, number_r=0, number_l=0;
        for(int i=0; i<number_of_faces;i++){
            is_inside = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line);
            if (is_inside>=2){
                number_l=number_l+1;
            }
            else{
                number_r=number_r+1;
            }
        }
        L->faces_in_node = new int [number_l];
        R->faces_in_node = new int[number_r];
        for(int i=0; i<number_of_faces;i++){
            is_inside = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line);
            if (is_inside>=2){
                l=l+1;
                L->faces_in_node[l]= node_faces[i];
            }
            else{
                r=r+1;
                R->faces_in_node[r]=node_faces[i];
            }
        }
    }

    else if ((fabs(ymax - ymin)>fabs(xmax-xmin))&&(fabs(ymax - ymin)>fabs(zmax-zmin))){ //y max axis
        boundary_line = (ymax-ymin)/2.0f+ymin;
       // std::cout<<"by "<<boundary_line<<"\n";
        l=-1, r=-1, number_r=0, number_l=0;
        for(int i=0; i<number_of_faces;i++){
            is_inside = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)+1]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)+1]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)+1]<=boundary_line);
            if (is_inside>=2){
                number_l=number_l+1;
            }
            else{
                number_r=number_r+1;
            }
        }
        L->faces_in_node = new int [ number_l];
        R->faces_in_node = new int[number_r];
        for(int i=0; i<number_of_faces;i++){
            is_inside = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)+1]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)+1]<=boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)+1]<=boundary_line);
            if (is_inside>=2){
                l=l+1;
                L->faces_in_node[l]= node_faces[i];
            }
            else{
                r=r+1;
                R->faces_in_node[r]=node_faces[i];
            }
        }
    }

    else{ 
        boundary_line = (zmax-zmin)/2.0f+zmin;
       // std::cout<<"bz "<<boundary_line<<"\n";
        l=-1, r=-1, number_r=0, number_l=0;
        for(int i=0; i<number_of_faces;i++){
            is_inside = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)+2]<boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)+2]<boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)+2]<boundary_line);
            if (is_inside>=2){
                number_l=number_l+1;
            } 
            else{
                number_r=number_r+1;
            }
        }
        L->faces_in_node = new int [ number_l];
        R->faces_in_node = new int[number_r];
        for(int i=0; i<number_of_faces;i++){
            is_inside = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)+2]<boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)+2]<boundary_line)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)+2]<boundary_line);
             if (is_inside>=2){
                l=l+1;
                L->faces_in_node[l]= node_faces[i];
            }
            else{        
                r=r+1;
                R->faces_in_node[r]=node_faces[i];
            }
        }
    }

    root->left_node = L;
    root->right_node = R;
//std::cout<<"l "<<number_l<<" r "<<number_r<<"\n";
    if ((number_l < previous_faces)&&(number_l>0)){
      //  std::cout<<"l "<<number_l<<"\n";
        int* faces_l = new int [3*number_l];
        for(int i=0; i<number_l;i++){
            faces_l[i] = L->faces_in_node[i];
        }
        build_tree(vertices, faces, faces_l, number_l, L, number_l);
        delete faces_l;
    }
    else{
        delete L;
        root->left_node= nullptr;
    }
    if ((number_r < previous_faces)&&(number_r>0)){
       int* faces_r = new int [3*number_r];
        for(int i=0; i<number_r;i++){
           faces_r[i] = R->faces_in_node[i];
        }
        build_tree(vertices, faces, faces_r, number_r, R, number_r);
        delete faces_r;
    }
    else{
        delete R;
        root->right_node = nullptr;
    }
}