#include <iostream>
#include "search_tree.hpp"

#define infinity FLT_MAX

search_tree::search_tree(){

}

void search_tree::build_tree(float* vertices, float* node_vertices, int number_of_vertices, search_tree* root, int previous_vertices){

    int k1=0, k2=0, k3=0; 
    float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;

    for(int i =0; i<number_of_vertices; i++){

        if (node_vertices[3*i]< xmin){
            xmin = node_vertices[3*i];
        }
         if (node_vertices[3*i+1]< ymin){
            ymin = node_vertices[3*i+1];
        }
         if (node_vertices[3*i+2]< zmin){
            zmin = node_vertices[3*i+2];
        }
        if (node_vertices[3*i]> xmax){
            xmax = node_vertices[3*i];
        }
         if (node_vertices[3*i+1]> ymax){
            ymax = node_vertices[3*i+1];
        }
         if (node_vertices[3*i+2]> zmax){
            zmax = node_vertices[3*i+2];
        }
    }
    root->parameters[0] = xmin;
    root->parameters[1] = xmax;
    root->parameters[2] = ymin;
    root->parameters[3] = ymax;
    root->parameters[4] = zmin;
    root->parameters[5] = zmax;

    search_tree*L= new search_tree;
    search_tree*R= new search_tree;

    int l=-1, r=-1, number_l=0, number_r=0;
    
    if ((fabs(xmax - xmin)>fabs(ymax-ymin))&&(fabs(xmax - xmin)>fabs(zmax-zmin))){ //x max axis
        float boundary_line = (xmax-xmin)/2.0f;
        l=-1, r=-1, number_r=0, number_l=0;
        for(int i=0; i<number_of_vertices;i++){
            if ((vertices[3*(root->vertices_in_node[i])])<= xmin+ boundary_line){
                number_l=number_l+1;
            }
            else{
                number_r=number_r+1;
            }
        }
        L->vertices_in_node = new int [number_l];
        R->vertices_in_node = new int[number_r];
        for(int i=0; i<number_of_vertices;i++){
            if ((vertices[3*(root->vertices_in_node[i])])<= xmin+boundary_line){
                l=l+1;
                L->vertices_in_node[l]= root->vertices_in_node[i];
            }
            else{
                r=r+1;
                R->vertices_in_node[r]=root->vertices_in_node[i];
            }
        }
    }

    else if ((fabs(ymax - ymin)>fabs(xmax-xmin))&&(fabs(ymax - ymin)>fabs(zmax-zmin))){ //y max axis
        float boundary_line = (ymax-ymin)/2.0f;
        l=-1, r=-1, number_r=0, number_l=0;
        for(int i=0; i<number_of_vertices;i++){
            if ((vertices[3*(root->vertices_in_node[i])+1])<=ymin+ boundary_line){
                number_l=number_l+1;
            }
            else{
                number_r=number_r+1;
            }
        }
        L->vertices_in_node = new int [ number_l];
        R->vertices_in_node = new int[number_r];
        for(int i=0; i<number_of_vertices;i++){
            if ((vertices[3*(root->vertices_in_node[i])+1])<= ymin+boundary_line){
                l=l+1;
                L->vertices_in_node[l]= root->vertices_in_node[i];
            }
            else{
                r=r+1;
                R->vertices_in_node[r]=root->vertices_in_node[i];
            }
        }
    }

    else{ 
        float boundary_line = (zmax-zmin)/2.0f;
        l=-1, r=-1, number_r=0, number_l=0;
        for(int i=0; i<number_of_vertices;i++){
            if ((vertices[3*(root->vertices_in_node[i])+2])<= zmin+ boundary_line){
                number_l=number_l+1;
            } 
            else{
                number_r=number_r+1;
            }
        }
        L->vertices_in_node = new int [ number_l];
        R->vertices_in_node = new int[number_r];
        for(int i=0; i<number_of_vertices;i++){
            if ((vertices[3*(root->vertices_in_node[i])+2])<=zmin+ boundary_line){
                l=l+1;
                L->vertices_in_node[l]= root->vertices_in_node[i];
            }
            else{        
                r=r+1;
                R->vertices_in_node[r]=root->vertices_in_node[i];
            }
        }
    }

    root->left_node = L;
    root->right_node = R;

    if ((number_l < previous_vertices)&&(number_l>0)){
        float* vertices_l = new float [3*number_l];
        for(int i=0; i<number_l;i++){
            vertices_l[3*i] = vertices[3*(L->vertices_in_node[i])];
            vertices_l[3*i+1] = vertices[3*(L->vertices_in_node[i])+1];
            vertices_l[3*i+2] = vertices[3*(L->vertices_in_node[i])+2];
        }
        build_tree(vertices, vertices_l, number_l, L, number_l);
        delete vertices_l;
    }
    else{
        delete L;
        root->left_node= nullptr;
    }
    if ((number_r < previous_vertices)&&(number_r>0)){
        float* vertices_r = new float [3*number_r];
        for(int i=0; i<number_r;i++){
            vertices_r[3*i] = vertices[3*(R->vertices_in_node[i])];
            vertices_r[3*i+1] = vertices[3*(R->vertices_in_node[i])+1];
            vertices_r[3*i+2] = vertices[3*(R->vertices_in_node[i])+2];
        }
        build_tree(vertices, vertices_r, number_r, R, number_r);
        delete vertices_r;
    }
    else{
        delete R;
        root->right_node = nullptr;
    }
}