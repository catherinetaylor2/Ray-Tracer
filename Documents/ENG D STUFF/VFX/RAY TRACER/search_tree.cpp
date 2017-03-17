#include <iostream>
#include "search_tree.hpp"
#include "vec3.hpp"

#define infinity FLT_MAX

void search_tree::build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree* root, int previous_faces){

    int k1=0, k2=0, k3=0; 
    float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;

    for(int i =0; i<number_of_faces; i++){
        for(int j=0; j<3; j++){
           // std::cout<<"z "<< vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2]<<"\n";
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
     //  std::cout<<"bz "<<boundary_line<<"\n";
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
//std::cout<<"l "<<number_l<<" r "<<number_r<<"\n";
    if ((number_l < previous_faces)&&(number_l>0)){
      //  std::cout<<"l "<<number_l<<"\n";
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
      //  std::cout<<"null "<<"\n";
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
     tmin_z = (parameters[4]- ray_point.get_z())*inv_direction.get_z();
     tmax_z = (parameters[5]- ray_point.get_z())*inv_direction.get_z();
//std::cout<<"1 x "<<tmin<<" "<<tmax<<" y "<<tmin_y<<" "<<tmax_y<<" z "<<tmin_z<<" "<<tmax_z<<"\n";
     if (tmin > tmax){
         std::swap(tmin, tmax);
     }
     if (tmin_y > tmax_y){
          std::swap(tmin_y, tmax_y);
     }
     
     if (tmin_z > tmax_z){
          a = tmin_z;
         tmin_z = tmax_z;
         tmax_z=a;
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

   //  std::cout<<"2 x "<<tmin<<" "<<tmax<<" y "<<tmin_y<<" "<<tmax_y<<" z "<<tmin_z<<" "<<tmax_z<<"\n";

     if ((tmin > tmax_z)|(tmin_z>tmax)){
         return 0;
     }
      if (tmin_z > tmin){
        tmin = tmin_z;
     }
     if (tmax_z < tmax){
         tmax = tmax_z;
     }
     if(tmin<0){
         return 0;
     }
     //  std::cout<<"3 x "<<tmin<<" "<<tmax<<" y "<<tmin_y<<" "<<tmax_y<<" z "<<tmin_z<<" "<<tmax_z<<"\n";
     return 1;
 }   

 float Bounding_box::get_tmax(void){
     return tmax;
 }
 float Bounding_box::get_tmin(void){
     return tmin;
 }
//  int search_tree::left_or_right(search_tree* root, vector3 eye, vector3 d){
//      float brr, brl, bll, blr, c;
//             if(root->right_node->right_node != nullptr){
//                 Bounding_box Brr(root->right_node->right_node->parameters[0],root->right_node->right_node->parameters[1], root->right_node->right_node->parameters[2],root->right_node->right_node->parameters[3],root->right_node->right_node->parameters[4],root->right_node->right_node->parameters[5]);
//                 brr = Brr.ray_box_intersection(eye, d);
//             }
//             else{
//                 brr=0;
//             }
//             if(root->right_node->left_node != nullptr){
//                 Bounding_box Brl(root->right_node->left_node->parameters[0],root->right_node->left_node->parameters[1], root->right_node->left_node->parameters[2],root->right_node->left_node->parameters[3],root->right_node->left_node->parameters[4],root->right_node->left_node->parameters[5]);
//                 brl = Brl.ray_box_intersection(eye, d);
//             }
//             else{
//                 brl=0;
//             }
//              if(root->left_node->left_node != nullptr){
//                 Bounding_box Bll(root->left_node->left_node->parameters[0],root->left_node->left_node->parameters[1], root->left_node->left_node->parameters[2],root->left_node->left_node->parameters[3],root->left_node->left_node->parameters[4],root->left_node->left_node->parameters[5]);
//                 bll = Bll.ray_box_intersection(eye, d);
//             }
//             else{
//                 bll=0;
//             }
//            c = bll +blr +brr+brl;
//             // if((bll ==0)&&(blr==0)&&(brr==0)&&(brl=0)){
//             //     return 0;
//             // }
//             if(root->left_node->right_node != nullptr){
//                 Bounding_box Blr(root->left_node->right_node->parameters[0],root->left_node->right_node->parameters[1], root->left_node->right_node->parameters[2],root->left_node->right_node->parameters[3],root->left_node->right_node->parameters[4],root->left_node->right_node->parameters[5]);
//                 blr = Blr.ray_box_intersection(eye, d);
//             }
//             else{
//                // std::cout<<"line 274 \n";
//                 blr=0;
//             }
//             if((fabs(brr)+fabs(brl)==0)&&(fabs(bll)+fabs(blr)!=0)){
//               return -1;
//             }
//             if((fabs(brr)+fabs(brl)!=0)&&(fabs(bll)+fabs(blr)==0)){
//               return 1;
//             }
//             else if (((fabs(brr)+fabs(brl))<(fabs(bll)+fabs(blr)))&&(fabs(brr)+fabs(brl)!=0)&&(fabs(bll)+fabs(blr)!=0)){
//                  return -1;
//               }
//             else if(((fabs(brr)+fabs(brl))>(fabs(bll)+fabs(blr)))&&(fabs(brr)+fabs(brl)!=0)&&(fabs(bll)+fabs(blr)!=0)){
//                 return 1;
//               }                     
//             // else{
//             //     return -1;
//             // }

//  }


 int* search_tree::traverse_tree(search_tree*root, vector3 eye, vector3 d, int* output){
     	Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
         int b1, b2;

    if(B_root.ray_box_intersection(eye, d)==1){       
        search_tree* current = root;
        if(root->right_node!=nullptr){
            Bounding_box B1(root->right_node->parameters[0],root->right_node->parameters[1], root->right_node->parameters[2],root->right_node->parameters[3],root->right_node->parameters[4],root->right_node->parameters[5]);
            b1 = B1.ray_box_intersection(eye, d);
           // std::cout<<"b1 "<<b1<<"\n";
        }
        else{
            b1=0;
        }
        if(root->left_node!=nullptr){
            Bounding_box B2(root->left_node->parameters[0],root->left_node->parameters[1], root->left_node->parameters[2],root->left_node->parameters[3],root->left_node->parameters[4],root->left_node->parameters[5]);
            b2 = B2.ray_box_intersection(eye, d);
        }
        else{
            b2=0;
        }
        if((b1!=1)&&(b2!=1)){
          // output = new int[1];
          root=current;
           output[0]=-1;
            return output;
           // delete no;
        }
        else if((b1!=1)&&(b2==1)){
            root = root->left_node;
        }
        else if((b1==1)&&(b2!=1)){
            root = root->right_node;
        }  
        if ((b1==1)&&(b2==1)){
           // output = new int[root->number_of_node_faces+1];
            output[0] = root->number_of_node_faces;
            //std::cout<<"yes "<<yes[0]<<"\n";
            for (int i = 1; i< root->number_of_node_faces+1; i++){
                output[i] = root->faces_in_node[i-1];
            }
            std::cout<<"all "<<output[0]<<" \n";
            root = current;
             return output;
         //
        }
        if((root->left_node!=nullptr)&&(root->right_node!=nullptr)&&((b1+b2)!=2)){
         std::cout<<root->left_node<<"\n";
            traverse_tree(root, eye, d, output);
        }
        else{
            //std::cout<<"root"<<root->number_of_node_faces<<" \n";
          //  output = new int[root->number_of_node_faces+1];
         // std::cout<<"int \n";
           output[0] = root->number_of_node_faces;
            for (int i = 1; i< root->number_of_node_faces+1; i++){
                output[i] = root->faces_in_node[i-1];
            }
            root = current;
            return output;
        //    delete yes;
        }      
    }
    else{
       //  output = new int[1];
      std::cout<<"line 373 \n";
           output[0]=-1;
            return output;
            //delete no;
    }
   //return -1;
    
 }