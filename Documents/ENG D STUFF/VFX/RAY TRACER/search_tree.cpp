#include <iostream>
#include "search_tree.hpp"
#include "vec3.hpp"
#include <vector>

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

    search_tree*L= new search_tree;
    search_tree*R= new search_tree;

    int l=-1, r=-1, number_l=0, number_r=0, is_inside;
    float boundary_line;

    if ((fabs(xmax - xmin)>fabs(ymax-ymin))&&(fabs(xmax - xmin)>fabs(zmax-zmin))){ //x max axis
        boundary_line = (xmax-xmin)/2.0f +xmin;
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
                L->faces_in_node[l]= root->faces_in_node[i];
            }
            else{
                r=r+1;
                R->faces_in_node[r]=root->faces_in_node[i];
            }
        }
    }

    else if ((fabs(ymax - ymin)>fabs(xmax-xmin))&&(fabs(ymax - ymin)>fabs(zmax-zmin))){ //y max axis
        boundary_line = (ymax-ymin)/2.0f+ymin;
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
                L->faces_in_node[l]= root->faces_in_node[i];
            }
            else{
                r=r+1;
                R->faces_in_node[r]=root->faces_in_node[i];
            }
        }
    }

    else{ 
        boundary_line = (zmax-zmin)/2.0f+zmin;
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
                L->faces_in_node[l]= root->faces_in_node[i];
            }
            else{        
                r=r+1;
                R->faces_in_node[r]=root->faces_in_node[i];
            }
        }
    }
    root->left_node = L;
    root->right_node = R;
    if ((number_l < previous_faces)&&(number_l>0)){
        int* faces_l = new int [3*number_l];
        for(int i=0; i<number_l;i++){
            faces_l[i] = L->faces_in_node[i];
        }
        L->number_of_node_faces = number_l;
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
        R->number_of_node_faces=number_r;
        build_tree(vertices, faces, faces_r, number_r, R, number_r);
        delete faces_r;
    }
    else{
        delete R;
        root->right_node = nullptr;
    }
 
}

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


void search_tree_8::build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree_8* root, int previous_faces){
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

    search_tree_8*node1= new search_tree_8;
    search_tree_8*node2= new search_tree_8;
    search_tree_8*node3= new search_tree_8;
    search_tree_8*node4= new search_tree_8;
    search_tree_8*node5= new search_tree_8;
    search_tree_8*node6= new search_tree_8;
    search_tree_8*node7= new search_tree_8;
    search_tree_8*node8= new search_tree_8;

    int n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0, is_inside1, is_inside2, is_inside3, is_inside4, is_inside5, is_inside6, is_inside7;
    float boundary_line1,boundary_line2,boundary_line3,boundary_line4,boundary_line5,boundary_line6,boundary_line7 ;

     if ((fabs(xmax - xmin)>fabs(ymax-ymin))&&(fabs(xmax - xmin)>fabs(zmax-zmin))){ 
        n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0;
        boundary_line1 = (xmax-xmin)/8.0f +xmin, boundary_line2 = 2*(xmax-xmin)/8.0f +xmin, boundary_line3 = 3*(xmax-xmin)/8.0f +xmin, boundary_line4 = 4*(xmax-xmin)/8.0f +xmin, boundary_line5 = 5*(xmax-xmin)/8.0f +xmin, boundary_line6 = 6*(xmax-xmin)/8.0f +xmin, boundary_line7 = 7*(xmax-xmin)/8.0f +xmin;
        for(int i=0; i<number_of_faces;i++){
            is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
            is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
            is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
            is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
            is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
            is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
            is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

            if (is_inside1>=2){
                number_1=number_1+1;
            }
            else if (is_inside2>=2){
                number_2=number_2+1;
            }
            else if (is_inside3>=2){
                number_3=number_3+1;
            }
            else if (is_inside4>=2){
                number_4=number_4+1;
            }
            else if (is_inside5>=2){
                number_5=number_5+1;
            }
            else if (is_inside6>=2){
                number_6=number_6+1;
            }
            else if (is_inside7>=2){
                number_7=number_7+1;
            }
            else{
                number_8 = number_8+1;
            }
        }
        node1->faces_in_node = new int [number_1];
        node2->faces_in_node = new int [number_2];
        node3->faces_in_node = new int[number_3];
        node4->faces_in_node = new int [number_4];
        node5->faces_in_node = new int[number_5];
        node6->faces_in_node = new int [number_6];
        node7->faces_in_node = new int[number_7];
        node8->faces_in_node = new int[number_8];
        for(int i=0; i<number_of_faces;i++){
            is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
            is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
            is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
            is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
            is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
            is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
            is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

            if (is_inside1>=2){
                n1=n1+1;
                node1->faces_in_node[n1]= root->faces_in_node[i];
            }
            else if (is_inside2>=2){
                n2=n2+1;
                node2->faces_in_node[n2]= root->faces_in_node[i];
            }
            else if (is_inside3>=2){
                n3=n3+1;
                node3->faces_in_node[n3]= root->faces_in_node[i];
            }
            else if (is_inside4>=2){
                n4=n4+1;
                node4->faces_in_node[n4]= root->faces_in_node[i];
            }
            else if (is_inside5>=2){
                n5=n5+1;
                node5->faces_in_node[n5]= root->faces_in_node[i];
            }
           else  if (is_inside6>=2){
                n6=n6+1;
                node6->faces_in_node[n6]= root->faces_in_node[i];
            }
             else if (is_inside7>=2){
                n7=n7+1;
                node7->faces_in_node[n7]=root->faces_in_node[i];
            }
            else{
                 n8=n8+1;
                node8->faces_in_node[n8]=root->faces_in_node[i];
            }
        }
    }
    else if ((fabs(ymax - ymin)>fabs(xmax-xmin))&&(fabs(ymax - ymin)>fabs(zmax-zmin))){ 
        n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0;
        boundary_line1 = (ymax-ymin)/8.0f +ymin, boundary_line2 = 2*(ymax-ymin)/8.0f +ymin, boundary_line3 = 3*(ymax-ymin)/8.0f +ymin, boundary_line4 = 4*(ymax-ymin)/8.0f +ymin, boundary_line5 = 5*(ymax-ymin)/8.0f +ymin, boundary_line6 = 6*(ymax-ymin)/8.0f +ymin, boundary_line7 = 7*(ymax-ymin)/8.0f +ymin;
        for(int i=0; i<number_of_faces;i++){
            is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
            is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
            is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
            is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
            is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
            is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
            is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

            if (is_inside1>=2){
                number_1=number_1+1;
            }
            else if (is_inside2>=2){
                number_2=number_2+1;
            }
            else if (is_inside3>=2){
                number_3=number_3+1;
            }
            else if (is_inside4>=2){
                number_4=number_4+1;
            }
            else if (is_inside5>=2){
                number_5=number_5+1;
            }
            else if (is_inside6>=2){
                number_6=number_6+1;
            }
             else if (is_inside7>=2){
                number_7=number_7+1;
            }
            else{
                number_8 = number_8+1;
            }

        }
        node1->faces_in_node = new int [number_1];
        node2->faces_in_node = new int [number_2];
        node3->faces_in_node = new int[number_3];
        node4->faces_in_node = new int [number_4];
        node5->faces_in_node = new int[number_5];
        node6->faces_in_node = new int [number_6];
        node7->faces_in_node = new int[number_7];
        node8->faces_in_node = new int[number_8];
        for(int i=0; i<number_of_faces;i++){
            is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
            is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
            is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
            is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
            is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
            is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
            is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

            if (is_inside1>=2){
                n1=n1+1;
                node1->faces_in_node[n1]= root->faces_in_node[i];
            }
            else if (is_inside2>=2){
                n2=n2+1;
                node2->faces_in_node[n2]= root->faces_in_node[i];
            }
            else if (is_inside3>=2){
                n3=n3+1;
                node3->faces_in_node[n3]= root->faces_in_node[i];
            }
            else if (is_inside4>=2){
                n4=n4+1;
                node4->faces_in_node[n4]= root->faces_in_node[i];
            }
            else if (is_inside5>=2){
                n5=n5+1;
                node5->faces_in_node[n5]= root->faces_in_node[i];
            }
           else  if (is_inside6>=2){
                n6=n6+1;
                node6->faces_in_node[n6]= root->faces_in_node[i];
            }
            else if (is_inside7>=2){
                n7=n7+1;
                node7->faces_in_node[n7]=root->faces_in_node[i];
            }
            else{
                 n8=n8+1;
                node8->faces_in_node[n8]=root->faces_in_node[i];
            }
        }
    }
  else{
  n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0;
        boundary_line1 = (zmax-zmin)/8.0f +zmin, boundary_line2 = 2*(zmax-zmin)/8.0f +zmin, boundary_line3 = 3*(zmax-zmin)/8.0f +zmin, boundary_line4 = 4*(zmax-zmin)/8.0f +zmin, boundary_line5 = 5*(zmax-zmin)/8.0f +zmin, boundary_line6 = 6*(zmax-zmin)/8.0f +zmin, boundary_line7 = 7*(zmax-zmin)/8.0f +zmin;
        for(int i=0; i<number_of_faces;i++){
            is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
            is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
            is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
            is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
            is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
            is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
            is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

            if (is_inside1>=2){
                number_1=number_1+1;
            }
            else if (is_inside2>=2){
                number_2=number_2+1;
            }
            else if (is_inside3>=2){
                number_3=number_3+1;
            }
            else if (is_inside4>=2){
                number_4=number_4+1;
            }
            else if (is_inside5>=2){
                number_5=number_5+1;
            }
            else if (is_inside6>=2){
                number_6=number_6+1;
            }
             else if (is_inside7>=2){
                number_7=number_7+1;
            }
            else{
                number_8 = number_8+1;
            }
        }
        node1->faces_in_node = new int [number_1];
        node2->faces_in_node = new int [number_2];
        node3->faces_in_node = new int[number_3];
        node4->faces_in_node = new int [number_4];
        node5->faces_in_node = new int[number_5];
        node6->faces_in_node = new int [number_6];
        node7->faces_in_node = new int[number_7];
        node8->faces_in_node = new int[number_8];
        for(int i=0; i<number_of_faces;i++){
            is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
            is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
            is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
            is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
            is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
            is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
            is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

            if (is_inside1>=2){
                n1=n1+1;
                node1->faces_in_node[n1]= root->faces_in_node[i];
            }
            else if (is_inside2>=2){
                n2=n2+1;
                node2->faces_in_node[n2]= root->faces_in_node[i];
            }
            else if (is_inside3>=2){
                n3=n3+1;
                node3->faces_in_node[n3]= root->faces_in_node[i];
            }
            else if (is_inside4>=2){
                n4=n4+1;
                node4->faces_in_node[n4]= root->faces_in_node[i];
            }
            else if (is_inside5>=2){
                n5=n5+1;
                node5->faces_in_node[n5]= root->faces_in_node[i];
            }
           else  if (is_inside6>=2){
                n6=n6+1;
                node6->faces_in_node[n6]= root->faces_in_node[i];
            }
            else if (is_inside7>=2){
                n7=n7+1;
                node7->faces_in_node[n7]=root->faces_in_node[i];
            }
            else{
                 n8=n8+1;
                node8->faces_in_node[n8]=root->faces_in_node[i];
            }
        }
    }
    root->node_1 = node1;
    root->node_2 = node2;
    root->node_3 = node3;
    root->node_4 = node4;
    root->node_5 = node5;
    root->node_6 = node6;
    root->node_7 = node7;
    root->node_8 = node8;
    if ((number_1 < previous_faces)&&(number_1>0)){
        int* faces_1 = new int [3*number_1];
        for(int i=0; i<number_1;i++){
            faces_1[i] = node1->faces_in_node[i];
        }
       node1->number_of_node_faces = number_1;
        build_tree(vertices, faces, faces_1, number_1, node1, number_1);
        delete faces_1;
    }
    else{
        delete node1;
        root->node_1= nullptr;
    }
 if ((number_2 < previous_faces)&&(number_2>0)){
        int* faces_2 = new int [3*number_2];
        for(int i=0; i<number_2;i++){
            faces_2[i] = node2->faces_in_node[i];
        }
       node2->number_of_node_faces = number_2;
        build_tree(vertices, faces, faces_2, number_2, node2, number_2);
        delete faces_2;
    }
    else{
        delete node2;
        root->node_2= nullptr;
    }
     if ((number_3 < previous_faces)&&(number_3>0)){
        int* faces_3 = new int [3*number_3];
        for(int i=0; i<number_3;i++){
            faces_3[i] = node3->faces_in_node[i];
        }
       node3->number_of_node_faces = number_3;
        build_tree(vertices, faces, faces_3, number_3, node3, number_3);
        delete faces_3;
    }
    else{
        delete node3;
        root->node_3= nullptr;
    }
     if ((number_4 < previous_faces)&&(number_4>0)){
        int* faces_4 = new int [3*number_4];
        for(int i=0; i<number_4;i++){
            faces_4[i] = node4->faces_in_node[i];
        }
       node4->number_of_node_faces = number_4;
        build_tree(vertices, faces, faces_4, number_4, node4, number_4);
        delete faces_4;
    }
    else{
        delete node4;
        root->node_4= nullptr;
    }
     if ((number_5 < previous_faces)&&(number_5>0)){
        int* faces_5 = new int [3*number_5];
        for(int i=0; i<number_5;i++){
            faces_5[i] = node5->faces_in_node[i];
        }
       node5->number_of_node_faces = number_5;
        build_tree(vertices, faces, faces_5, number_5, node5, number_5);
        delete faces_5;
    }
    else{
        delete node5;
        root->node_5= nullptr;
    }
     if ((number_6 < previous_faces)&&(number_6>0)){
        int* faces_6 = new int [3*number_6];
        for(int i=0; i<number_6;i++){
            faces_6[i] = node6->faces_in_node[i];
        }
       node6->number_of_node_faces = number_6;
        build_tree(vertices, faces, faces_6, number_6, node6, number_6);
        delete faces_6;
    }
    else{
        delete node6;
        root->node_6= nullptr;
    }
     if ((number_7 < previous_faces)&&(number_7>0)){
        int* faces_7 = new int [3*number_7];
        for(int i=0; i<number_7;i++){
            faces_7[i] = node7->faces_in_node[i];
        }
       node7->number_of_node_faces = number_7;
        build_tree(vertices, faces, faces_7, number_7, node7, number_7);
        delete faces_7;
    }
    else{
        delete node7;
        root->node_7= nullptr;
    }
    if ((number_8 < previous_faces)&&(number_8>0)){
        int* faces_8 = new int [3*number_8];
        for(int i=0; i<number_8;i++){
            faces_8[i] = node8->faces_in_node[i];
        }
        node8->number_of_node_faces = number_8;
        build_tree(vertices, faces, faces_8, number_8, node8, number_8);
        delete faces_8;
    }
    else{
        delete node8;
        root->node_8= nullptr;
    }
}

void search_tree_8::traverse_tree(search_tree_8*root, vector3 eye, vector3 d, std::vector<float> *output){
    Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
    if(((root->node_1==nullptr))&&((root->node_2==nullptr))&&((root->node_3==nullptr))&&((root->node_4==nullptr))&&((root->node_5==nullptr))&&((root->node_6==nullptr))&&((root->node_7==nullptr))&&((root->node_8==nullptr))){
        if((B_root.ray_box_intersection(eye, d)==1)){        
            for (int i = 0; i<root->number_of_node_faces; i++){
                (*output).push_back( root->faces_in_node[i]);
            }         
        }   
    }
     if((root->node_1!=nullptr)){
         traverse_tree(root->node_1, eye, d, output);
     }
     if (root->node_2!=nullptr){
        traverse_tree(root->node_2, eye, d, output);
     }
     if (root->node_3!=nullptr){
        traverse_tree(root->node_3, eye, d, output);
     }
     if ((root->node_4!=nullptr)){
        traverse_tree(root->node_4, eye, d, output);
     }
     if ((root->node_5!=nullptr)){
        traverse_tree(root->node_5, eye, d, output);
     }
     if((root->node_6!=nullptr)){
        traverse_tree(root->node_6, eye, d, output);
     }
     if ((root->node_7!=nullptr)){
        traverse_tree(root->node_7, eye, d, output);
     }
     if ((root->node_8!=nullptr)){
        traverse_tree(root->node_8, eye, d, output);
     }  
} 

std::vector<search_tree*> search_tree::leaf_nodes(float* vertices, int*faces, int number_of_faces){
     float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;
std::vector<search_tree*> leaf_nodes;

    for(int i = 0; i<number_of_faces; i++){ // make list of leaf_nodes.
        xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;
        search_tree* leaf = new search_tree;
        leaf->number_of_node_faces = 1; 
        leaf->faces_in_node= new int [1];
        leaf->faces_in_node[0]=i;

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
        leaf->parameters[0] = xmin;
        leaf->parameters[1] = xmax;
        leaf->parameters[2] = ymin;
        leaf->parameters[3] = ymax;
        leaf->parameters[4] = zmin;
        leaf->parameters[5] = zmax;
        leaf->left_node=nullptr;
        leaf->right_node=nullptr;
        (leaf_nodes).push_back(leaf);
    }
    return leaf_nodes;
}

void search_tree::build_tree_leaves(float* vertices, int* faces, std::vector<search_tree*> leaf_nodes, search_tree*root ){
 
    float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;

    search_tree* first = new search_tree;
    search_tree* second = new search_tree;
    search_tree*temp = new search_tree;
    first = leaf_nodes[0];
 
    if(leaf_nodes[1]==nullptr){
        root = first;
       std::cout<<root->number_of_node_faces<<"\n";
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
    //std::cout <<"line 839 \n";
        temp->parameters[0] = xmin;
       temp->parameters[1] = xmax;
       temp->parameters[2] = ymin;
        temp->parameters[3] = ymax;
        temp->parameters[4] = zmin;
        temp->parameters[5] = zmax;

        (leaf_nodes).push_back(temp);
        // delete first;
        // delete second;
       // delete temp;    
        build_tree_leaves(vertices, faces, leaf_nodes, root);  

    }
}