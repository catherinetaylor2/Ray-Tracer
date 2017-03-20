#include <iostream>
#include "search_tree.hpp"
#include "vec3.hpp"
#include <vector>

#define infinity FLT_MAX

 Bounding_box::Bounding_box(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax){
     parameters[0] = xmin;
     parameters[1] = xmax;
     parameters[2] = ymin;
     parameters[3] = ymax;
     parameters[4] = zmin;
     parameters[5] = zmax;
 }

 int Bounding_box::ray_box_intersection(vector3 ray_point, vector3 ray_direction){
    float tmin_y, tmax_y, tmin_z, tmax_z, a;
    vector3 inv_direction(1/ray_direction.get_x(), 1/ray_direction.get_y(), 1/ray_direction.get_z());

     tmin = (parameters[0]- ray_point.get_x())*inv_direction.get_x();
     tmax = (parameters[1]- ray_point.get_x())*inv_direction.get_x();

     if((ray_direction.get_x()==0)&&(ray_point.get_x()<parameters[0])&&(ray_point.get_x()>parameters[1])){
         return 0;
     }
         if((ray_direction.get_y()==0)&&(ray_point.get_y()<parameters[2])&&(ray_point.get_y()>parameters[3])){
         return 0;
     }
         if((ray_direction.get_z()==0)&&(ray_point.get_z()<parameters[4])&&(ray_point.get_z()>parameters[5])){
         return 0;
     }
     tmin_y = (parameters[2]- ray_point.get_y())*inv_direction.get_y();
     tmax_y = (parameters[3]- ray_point.get_y())*inv_direction.get_y();
     if (tmin > tmax){
         std::swap(tmin, tmax);
     }
     if (tmin_y > tmax_y){
          std::swap(tmin_y, tmax_y);
     }
  

     if ((tmin > tmax_y)||(tmin_y>tmax)){
         return 0;
     }
     if (tmin_y > tmin){
        tmin = tmin_y;
     }
     if (tmax_y < tmax){
         tmax = tmax_y;
     }        
     tmin_z = (parameters[4]- ray_point.get_z())*inv_direction.get_z();
     tmax_z = (parameters[5]- ray_point.get_z())*inv_direction.get_z();
     if (tmin_z > tmax_z){
          a = tmin_z;
         tmin_z = tmax_z;
         tmax_z=a;
     }
     if ((tmin > tmax_z)|(tmin_z>tmax)){
         return 0;
     }
      if (tmin_z > tmin){
        tmin = tmin_z;
     }
     if (tmax_z < tmax){
         tmax = tmax_z;
     } 
     return 1;
     
 }   

 float Bounding_box::get_tmax(void){
     return tmax;
 }
 float Bounding_box::get_tmin(void){
     return tmin;
 }


void search_tree::traverse_tree(search_tree*root, vector3 eye, vector3 d, std::vector<float> *output){
    Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
    if(((root->left_node==nullptr))&&((root->right_node==nullptr))){
        if((B_root.ray_box_intersection(eye, d)==1)){        
            for (int i = 0; i<root->number_of_node_faces; i++){
                (*output).push_back( root->faces_in_node[i]);
            }         
        }   
    }
    if ((root->right_node!=nullptr)||(root->left_node!=nullptr)) {
        traverse_tree(root->right_node, eye, d, output);
        traverse_tree(root->left_node, eye, d, output);
    }     
} 

void search_tree::find_parameters(int i, float* vertices,int*faces, std::vector<float> *parameters){
    float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;
    
        for(int j=0; j<3; j++){
            if (vertices[3*(faces[3*i+j]-1)]< xmin){
            xmin = vertices[3*(faces[3*i+j]-1)];
            }
            if (vertices[3*(faces[3*i+j]-1)+1]< ymin){
            ymin = vertices[3*(faces[3*i+j]-1)+1];
            }
            if (vertices[3*(faces[3*i+j]-1)+2]< zmin){
            zmin = vertices[3*(faces[3*i+j]-1)+2];
            }
            if (vertices[3*(faces[3*i+j]-1)]> xmax){
            xmax = vertices[3*(faces[3*i+j]-1)];
            }
            if (vertices[3*(faces[3*i+j]-1)+1]> ymax){
            ymax =vertices[3*(faces[3*i+j]-1)+1];
            }
            if (vertices[3*(faces[3*i+j]-1)+2]> zmax){
            zmax = vertices[3*(faces[3*i+j]-1)+2];
            }
        }
   
    *parameters = {xmin, xmax, ymin, ymax, zmin, zmax};
    }

void search_tree::leaf_nodes(float* vertices, int*faces, int number_of_faces,  std::vector<search_tree*> *leaf_nodes){
    std::vector<float> parameters;
    for(int i = 0; i<number_of_faces; i++){ // make list of leaf_nodes.
        search_tree* leaf = new search_tree;
        leaf->number_of_node_faces = 1; 
        leaf->faces_in_node= new int [1];
        leaf->faces_in_node[0]=i;
        parameters.clear();
        search_tree::find_parameters(i, vertices, faces, &parameters );
        for(int j =0; j<6;j++){
             leaf->parameters[j] = parameters[j];
        }
        leaf->left_node=nullptr;
        leaf->right_node=nullptr;
        (*leaf_nodes).push_back(leaf);
    }
}

void search_tree::build_tree(float* vertices, int* faces, std::vector<search_tree*> leaf_nodes, search_tree**root ){
    float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;
    std::vector<float> parameters;
    search_tree* first = new search_tree;
    search_tree* second = new search_tree;
    search_tree*temp = new search_tree;
    first = leaf_nodes[0];

    if(leaf_nodes[1]==nullptr){
       *root = first;
        delete second;
        delete temp; 
        return;
    }
    else{
        second = leaf_nodes[1];
        temp->left_node = first;
        temp->right_node = second;
        temp->number_of_node_faces = first->number_of_node_faces+second->number_of_node_faces;
        leaf_nodes.erase (leaf_nodes.begin(),leaf_nodes.begin()+2);
        temp->faces_in_node = new int [temp->number_of_node_faces];
        for(int i=0; i<first->number_of_node_faces; i++){
            temp->faces_in_node[i] = first->faces_in_node[i];
        }
        for(int i = first->number_of_node_faces; i<first->number_of_node_faces+second->number_of_node_faces;i++){
            temp->faces_in_node[i] = second->faces_in_node[i-first->number_of_node_faces];
        };
        xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;
        for(int i =0; i<temp->number_of_node_faces; i++){
                for(int j=0; j<3; j++){
                    if (vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)]< xmin){
                        xmin = vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)];
                    }
                    if (vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+1]< ymin){
                        ymin = vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+1];
                    }
                    if (vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+2]< zmin){
                        zmin = vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+2];
                    }
                    if (vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)]> xmax){
                        xmax = vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)];
                    }
                    if (vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+1]> ymax){
                        ymax =vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+1];
                    }
                    if (vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+2]> zmax){
                        zmax = vertices[3*(faces[3*(temp->faces_in_node[i])+j]-1)+2];
                    }
                }
            }
            temp->parameters[0] = xmin;
            temp->parameters[1] = xmax;
            temp->parameters[2] = ymin;
            temp->parameters[3] = ymax;
            temp->parameters[4] = zmin;
            temp->parameters[5] = zmax;

            (leaf_nodes).push_back(temp);
            build_tree(vertices, faces, leaf_nodes, root);  
    }
}

