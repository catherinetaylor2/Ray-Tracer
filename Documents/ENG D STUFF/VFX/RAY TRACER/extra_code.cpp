// ray tracer code for sphere on reflective surface


    //sphere sphere1(0,0,0,1,RED);
    //sphere sphere2(-1,0,0,1,BLUE);
    //triangle triangle1(0,3,2,-5,0,2,4,0,2,BLUE);
    //sphere1.set_lighting_constants(0.6, 0.7*255, 0.1, 600);
    //sphere2.set_lighting_constants(0.6, 0, 0.2, 600);
    //triangle1.set_lighting_constants(0.6, 0.5*255, 0.1, 800);
    //plane plane1(0, -1, 0 , 2 ,3, 20, 2,-4, -10,GREY);
    //plane1.set_lighting_constants(0.4, 0.8*255,0.1,300);

    

          //  float t1 = sphere1.Sphere_ray_intersection( eye, d);
                 // float t2 = abs(plane1.ray_plane_intersection(eye,d)*(plane1.ray_plane_intersection(eye,d)>0));
        // float t2 = sphere2.Sphere_ray_intersection( eye, d);
        //float t2 = triangle1.ray_triangle_intersection(eye,d);

        //         if ((t1 != 0)&&(t2!=0)){            
//             if (t1<t2){
         
//                 float t=t1;
//                 vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
//                 vector3 l = sun.get_light_direction(point); 
//                 vector3 normal=sphere1.find_normal(point); 
               
//                 vector3 RGB = sphere1.determine_colour(point, l, d, sun, normal, myscene,1);



//                 img[x] = RGB.get_x();
//                 img[x+1]=RGB.get_y();
//                 img[x+2]=RGB.get_z();  
//              }
//             else if(t2<t1){
//                 float t=t2;
//                 vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
//                 vector3 l = sun.get_light_direction(point); 

//                  vector3 normal=plane1.get_plane_normal(); 

//                 // vector3 normal=sphere2.find_normal(point); 
//                 // vector3 RGB = sphere2.determine_colour(point, l, d, sun, normal, myscene,1);

//                 // vector3 normal=triangle1.get_triangle_normal(triangle1.get_vertex1(), triangle1.get_vertex2(), triangle1.get_vertex3());  
//                 // vector3 RGB = triangle1.determine_colour(point, l, d, sun, normal, myscene,1);

               


//  vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,1);
                                
//                 img[x] = RGB.get_x();
//                 img[x+1]=RGB.get_y();
//                 img[x+2]=RGB.get_z(); 


   
//             }
//        }
//         else if ((t1 != 0)&&(t2==0)){
//             float t=t1;
//             vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
//             vector3 l = sun.get_light_direction(point); 
//             vector3 normal=sphere1.find_normal(point); 

//         float ss = plane1.ray_plane_intersection(point,l);   
// //float ss = sphere2.Sphere_ray_intersection( point, l);
//          // float ss = triangle1.ray_triangle_intersection( point, l);
//             int s = (ss<=0);
//            vector3 RGB = sphere1.determine_colour(point, l, d, sun, normal, myscene,s);
             
//             img[x] = RGB.get_x();
//             img[x+1]=RGB.get_y();
//             img[x+2]=RGB.get_z();  
//         }
//         else if ((t1 == 0)&&(t2!=0)){
//             float t=t2;
//             vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
//             vector3 l = sun.get_light_direction(point); 
//            //vector3 normal=triangle1.get_triangle_normal(triangle1.get_vertex1(), triangle1.get_vertex2(), triangle1.get_vertex3());  
//             // vector3 normal=sphere2.find_normal(point); 

             
//              vector3 normal=plane1.get_plane_normal(); 
               

//             float ss = sphere1.Sphere_ray_intersection( point, l);
//             int s = (ss<=0);
//          // vector3 RGB = triangle1.determine_colour(point, l, d, sun, normal, myscene,s);
//              //vector3 RGB = sphere2.determine_colour(point, l, d, sun, normal, myscene,s);

//               //multiple refelections
//                 vector3 R=normal.vec_scal_mult(2*normal.dotproduct(normal, normal.vec_scal_mult(-1,d)),normal);
//                 vector3 H = R.vec_add(R, normal.vec_scal_mult(1,d));
             
//                 H.normalize();
//                 float t3 = sphere1.Sphere_ray_intersection( point, H);
              
             
//                 if (t3!=0){
//                          vector3 point2 = d.vec_add(point, d.vec_scal_mult(t3,H));
//                         //  cout<<"px "<<point.get_x()<<" ";
//                         //   cout<<"py "<<point.get_y()<<" ";
//                         //    cout<<"pz "<<point.get_z()<<"\n";
//           vector3 l2 = sun.get_light_direction(point2); 
//           vector3 normal2=sphere1.find_normal(point2); 
//                                vector3 RGB2 = sphere1.determine_colour(point2, l2, d, sun, normal2, myscene,s);

//                                vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,s);
//                                 float R,G,B;
//                                 R=  RGB2.get_x()+RGB.get_x();
//                                 if (R>255){
//                                     R=255;
//                                 }
//                                 G = RGB2.get_y()+RGB.get_y();
//                                 if (G>255){
//                                     G=255;
//                                 }
//                                B=RGB2.get_z()+RGB.get_z();  
//                                if(B>255){
//                                    B=255;
//                                }
//                 img[x] = R;
//                 img[x+1]= G;
//                 img[x+2]= B;

             

//                 }
//                 else if (t3==0){
//                                 vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,s);
                                
//                 img[x] = RGB.get_x();
//                 img[x+1]=RGB.get_y();
//                 img[x+2]=RGB.get_z(); 

//                 }
            
//             //  vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,s);
//             // img[x] = RGB.get_x();
//             // img[x+1]=RGB.get_y();
//             // img[x+2]=RGB.get_z();  
//         }
//         else{
//             img[x]=0;
//             img[x+1]=0;
//             img[x+2]=0; 
//         }
//     }
  

  //GOURARD SHADING EXTRAS

  // vector3 l1 = sun.get_light_direction(point1);
				// vector3 l2= sun.get_light_direction(point2);
				// vector3 l3 = sun.get_light_direction(point3);

// vector3 RGB2 = tri.determine_colour(point2, l2, d, sun, N2, myscene,s);
// vector3 RGB3 = tri.determine_colour(point3, l3, d, sun, N3, myscene,s);
		// R = RGB1.get_x()*alpha1+RGB2.get_x()*alpha2+RGB3.get_x()*alpha3;
		// 		G = RGB1.get_y()*alpha1+RGB2.get_y()*alpha2+RGB3.get_y()*alpha3;
		// 		Bc = RGB1.get_z()alpha1+RGB2.get_z()*alpha2+RGB3.get_z()*alpha3;


    

    // if ((current->left_node==nullptr)&&(current->right_node==nullptr)&&(B_root.ray_box_intersection(eye, d)==1)){
    //     std::cout<<"in here"<<root->number_of_node_faces<<" \n";
    //     output[0] = current->number_of_node_faces;
    //     for (int i = 1; i< current->number_of_node_faces+1; i++){
    //         output[i] = current->faces_in_node[i-1];
    //     //    std::cout<<root->faces_in_node[i-1]<<"\n";
    //     }            
    //     return output;  
    // }
    // else if ((current->left_node!=nullptr)|(current->right_node!=nullptr)){
    //     if (current->left_node!=nullptr){
    //     std::cout<<"line 303 \n";
    //       output=  traverse_tree(current->left_node, eye, d, output);
    //     }
    //    if { 
    //         std::cout<<"line 308 \n";

    //        output =  traverse_tree(current->right_node, eye, d, output);
    //     }
        
    // }
    // else{
    //     // std::cout<<"line 306 \n";
    //         output[0]=-1;
    //         return output;
    //     }


    //-----------------------------------------------------------------------------------------------------------------------------------------------------------
    //octave search traverse_tree

// class search_tree_8{
//        public:
//             search_tree_8 *node_1;
//             search_tree_8 *node_2;
//             search_tree_8 *node_3;
//             search_tree_8 *node_4;
//             search_tree_8 *node_5;
//             search_tree_8 *node_6;
//             search_tree_8 *node_7;
//             search_tree_8 *node_8;

//             int*faces_in_node;
//             float parameters [6];
//             int number_of_node_faces;
//             static void build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree_8* root, int previous_faces);
//             static void traverse_tree(search_tree_8*root, vector3 eye, vector3 d, std::vector<float> *output);
//     private:

// };


//     void search_tree_8::build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree_8* root, int previous_faces){
//     int k1=0, k2=0, k3=0; 
//     float xmin = infinity, ymin = infinity, zmin = infinity, xmax=0, ymax=0, zmax = 0;
//   for(int i =0; i<number_of_faces; i++){
//         for(int j=0; j<3; j++){
//             if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)]< xmin){
//                 xmin = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)];
//             }
//             if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1]< ymin){
//                 ymin = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1];
//             }
//             if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2]< zmin){
//                 zmin = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2];
//             }
//             if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)]> xmax){
//                 xmax = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)];
//             }
//             if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1]> ymax){
//                 ymax =vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+1];
//             }
//             if (vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2]> zmax){
//                 zmax = vertices[3*(faces[3*(root->faces_in_node[i])+j]-1)+2];
//             }
//         }
//     }
//     root->parameters[0] = xmin;
//     root->parameters[1] = xmax;
//     root->parameters[2] = ymin;
//     root->parameters[3] = ymax;
//     root->parameters[4] = zmin;
//     root->parameters[5] = zmax;

//     search_tree_8*node1= new search_tree_8;
//     search_tree_8*node2= new search_tree_8;
//     search_tree_8*node3= new search_tree_8;
//     search_tree_8*node4= new search_tree_8;
//     search_tree_8*node5= new search_tree_8;
//     search_tree_8*node6= new search_tree_8;
//     search_tree_8*node7= new search_tree_8;
//     search_tree_8*node8= new search_tree_8;

//     int n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0, is_inside1, is_inside2, is_inside3, is_inside4, is_inside5, is_inside6, is_inside7;
//     float boundary_line1,boundary_line2,boundary_line3,boundary_line4,boundary_line5,boundary_line6,boundary_line7 ;

//      if ((fabs(xmax - xmin)>fabs(ymax-ymin))&&(fabs(xmax - xmin)>fabs(zmax-zmin))){ 
//         n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0;
//         boundary_line1 = (xmax-xmin)/8.0f +xmin, boundary_line2 = 2*(xmax-xmin)/8.0f +xmin, boundary_line3 = 3*(xmax-xmin)/8.0f +xmin, boundary_line4 = 4*(xmax-xmin)/8.0f +xmin, boundary_line5 = 5*(xmax-xmin)/8.0f +xmin, boundary_line6 = 6*(xmax-xmin)/8.0f +xmin, boundary_line7 = 7*(xmax-xmin)/8.0f +xmin;
//         for(int i=0; i<number_of_faces;i++){
//             is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
//             is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
//             is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
//             is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
//             is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
//             is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
//             is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

//             if (is_inside1>=2){
//                 number_1=number_1+1;
//             }
//             else if (is_inside2>=2){
//                 number_2=number_2+1;
//             }
//             else if (is_inside3>=2){
//                 number_3=number_3+1;
//             }
//             else if (is_inside4>=2){
//                 number_4=number_4+1;
//             }
//             else if (is_inside5>=2){
//                 number_5=number_5+1;
//             }
//             else if (is_inside6>=2){
//                 number_6=number_6+1;
//             }
//             else if (is_inside7>=2){
//                 number_7=number_7+1;
//             }
//             else{
//                 number_8 = number_8+1;
//             }
//         }
//         node1->faces_in_node = new int [number_1];
//         node2->faces_in_node = new int [number_2];
//         node3->faces_in_node = new int[number_3];
//         node4->faces_in_node = new int [number_4];
//         node5->faces_in_node = new int[number_5];
//         node6->faces_in_node = new int [number_6];
//         node7->faces_in_node = new int[number_7];
//         node8->faces_in_node = new int[number_8];
//         for(int i=0; i<number_of_faces;i++){
//             is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
//             is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
//             is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
//             is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
//             is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
//             is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
//             is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

//             if (is_inside1>=2){
//                 n1=n1+1;
//                 node1->faces_in_node[n1]= root->faces_in_node[i];
//             }
//             else if (is_inside2>=2){
//                 n2=n2+1;
//                 node2->faces_in_node[n2]= root->faces_in_node[i];
//             }
//             else if (is_inside3>=2){
//                 n3=n3+1;
//                 node3->faces_in_node[n3]= root->faces_in_node[i];
//             }
//             else if (is_inside4>=2){
//                 n4=n4+1;
//                 node4->faces_in_node[n4]= root->faces_in_node[i];
//             }
//             else if (is_inside5>=2){
//                 n5=n5+1;
//                 node5->faces_in_node[n5]= root->faces_in_node[i];
//             }
//            else  if (is_inside6>=2){
//                 n6=n6+1;
//                 node6->faces_in_node[n6]= root->faces_in_node[i];
//             }
//              else if (is_inside7>=2){
//                 n7=n7+1;
//                 node7->faces_in_node[n7]=root->faces_in_node[i];
//             }
//             else{
//                  n8=n8+1;
//                 node8->faces_in_node[n8]=root->faces_in_node[i];
//             }
//         }
//     }
//     else if ((fabs(ymax - ymin)>fabs(xmax-xmin))&&(fabs(ymax - ymin)>fabs(zmax-zmin))){ 
//         n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0;
//         boundary_line1 = (ymax-ymin)/8.0f +ymin, boundary_line2 = 2*(ymax-ymin)/8.0f +ymin, boundary_line3 = 3*(ymax-ymin)/8.0f +ymin, boundary_line4 = 4*(ymax-ymin)/8.0f +ymin, boundary_line5 = 5*(ymax-ymin)/8.0f +ymin, boundary_line6 = 6*(ymax-ymin)/8.0f +ymin, boundary_line7 = 7*(ymax-ymin)/8.0f +ymin;
//         for(int i=0; i<number_of_faces;i++){
//             is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
//             is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
//             is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
//             is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
//             is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
//             is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
//             is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

//             if (is_inside1>=2){
//                 number_1=number_1+1;
//             }
//             else if (is_inside2>=2){
//                 number_2=number_2+1;
//             }
//             else if (is_inside3>=2){
//                 number_3=number_3+1;
//             }
//             else if (is_inside4>=2){
//                 number_4=number_4+1;
//             }
//             else if (is_inside5>=2){
//                 number_5=number_5+1;
//             }
//             else if (is_inside6>=2){
//                 number_6=number_6+1;
//             }
//              else if (is_inside7>=2){
//                 number_7=number_7+1;
//             }
//             else{
//                 number_8 = number_8+1;
//             }

//         }
//         node1->faces_in_node = new int [number_1];
//         node2->faces_in_node = new int [number_2];
//         node3->faces_in_node = new int[number_3];
//         node4->faces_in_node = new int [number_4];
//         node5->faces_in_node = new int[number_5];
//         node6->faces_in_node = new int [number_6];
//         node7->faces_in_node = new int[number_7];
//         node8->faces_in_node = new int[number_8];
//         for(int i=0; i<number_of_faces;i++){
//             is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
//             is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
//             is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
//             is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
//             is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
//             is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
//             is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

//             if (is_inside1>=2){
//                 n1=n1+1;
//                 node1->faces_in_node[n1]= root->faces_in_node[i];
//             }
//             else if (is_inside2>=2){
//                 n2=n2+1;
//                 node2->faces_in_node[n2]= root->faces_in_node[i];
//             }
//             else if (is_inside3>=2){
//                 n3=n3+1;
//                 node3->faces_in_node[n3]= root->faces_in_node[i];
//             }
//             else if (is_inside4>=2){
//                 n4=n4+1;
//                 node4->faces_in_node[n4]= root->faces_in_node[i];
//             }
//             else if (is_inside5>=2){
//                 n5=n5+1;
//                 node5->faces_in_node[n5]= root->faces_in_node[i];
//             }
//            else  if (is_inside6>=2){
//                 n6=n6+1;
//                 node6->faces_in_node[n6]= root->faces_in_node[i];
//             }
//             else if (is_inside7>=2){
//                 n7=n7+1;
//                 node7->faces_in_node[n7]=root->faces_in_node[i];
//             }
//             else{
//                  n8=n8+1;
//                 node8->faces_in_node[n8]=root->faces_in_node[i];
//             }
//         }
//     }
//   else{
//   n1=-1, n2=-1,n3=-1, n4=-1,n5=-1, n6=-1,n7=-1, n8=-1, number_1=0, number_2=0,number_3=0, number_4=0,number_5=0, number_6=0,number_7=0, number_8=0;
//         boundary_line1 = (zmax-zmin)/8.0f +zmin, boundary_line2 = 2*(zmax-zmin)/8.0f +zmin, boundary_line3 = 3*(zmax-zmin)/8.0f +zmin, boundary_line4 = 4*(zmax-zmin)/8.0f +zmin, boundary_line5 = 5*(zmax-zmin)/8.0f +zmin, boundary_line6 = 6*(zmax-zmin)/8.0f +zmin, boundary_line7 = 7*(zmax-zmin)/8.0f +zmin;
//         for(int i=0; i<number_of_faces;i++){
//             is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
//             is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
//             is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
//             is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
//             is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
//             is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
//             is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

//             if (is_inside1>=2){
//                 number_1=number_1+1;
//             }
//             else if (is_inside2>=2){
//                 number_2=number_2+1;
//             }
//             else if (is_inside3>=2){
//                 number_3=number_3+1;
//             }
//             else if (is_inside4>=2){
//                 number_4=number_4+1;
//             }
//             else if (is_inside5>=2){
//                 number_5=number_5+1;
//             }
//             else if (is_inside6>=2){
//                 number_6=number_6+1;
//             }
//              else if (is_inside7>=2){
//                 number_7=number_7+1;
//             }
//             else{
//                 number_8 = number_8+1;
//             }
//         }
//         node1->faces_in_node = new int [number_1];
//         node2->faces_in_node = new int [number_2];
//         node3->faces_in_node = new int[number_3];
//         node4->faces_in_node = new int [number_4];
//         node5->faces_in_node = new int[number_5];
//         node6->faces_in_node = new int [number_6];
//         node7->faces_in_node = new int[number_7];
//         node8->faces_in_node = new int[number_8];
//         for(int i=0; i<number_of_faces;i++){
//             is_inside1 = (vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line1)+(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line1);
//             is_inside2 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line1))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line2)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line1));
//             is_inside3 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line2))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line3)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line2));
//             is_inside4 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line3))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line4)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line3));
//             is_inside5 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line4))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line5)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line4));
//             is_inside6 = ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line5))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line6)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line5));
//             is_inside7= ((vertices[3*(faces[3*(root->faces_in_node[i])]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+1]-1)]>boundary_line6))+((vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]<=boundary_line7)&&(vertices[3*(faces[3*(root->faces_in_node[i])+2]-1)]>boundary_line6));

//             if (is_inside1>=2){
//                 n1=n1+1;
//                 node1->faces_in_node[n1]= root->faces_in_node[i];
//             }
//             else if (is_inside2>=2){
//                 n2=n2+1;
//                 node2->faces_in_node[n2]= root->faces_in_node[i];
//             }
//             else if (is_inside3>=2){
//                 n3=n3+1;
//                 node3->faces_in_node[n3]= root->faces_in_node[i];
//             }
//             else if (is_inside4>=2){
//                 n4=n4+1;
//                 node4->faces_in_node[n4]= root->faces_in_node[i];
//             }
//             else if (is_inside5>=2){
//                 n5=n5+1;
//                 node5->faces_in_node[n5]= root->faces_in_node[i];
//             }
//            else  if (is_inside6>=2){
//                 n6=n6+1;
//                 node6->faces_in_node[n6]= root->faces_in_node[i];
//             }
//             else if (is_inside7>=2){
//                 n7=n7+1;
//                 node7->faces_in_node[n7]=root->faces_in_node[i];
//             }
//             else{
//                  n8=n8+1;
//                 node8->faces_in_node[n8]=root->faces_in_node[i];
//             }
//         }
//     }
//     root->node_1 = node1;
//     root->node_2 = node2;
//     root->node_3 = node3;
//     root->node_4 = node4;
//     root->node_5 = node5;
//     root->node_6 = node6;
//     root->node_7 = node7;
//     root->node_8 = node8;
//     if ((number_1 < previous_faces)&&(number_1>0)){
//         int* faces_1 = new int [3*number_1];
//         for(int i=0; i<number_1;i++){
//             faces_1[i] = node1->faces_in_node[i];
//         }
//        node1->number_of_node_faces = number_1;
//         build_tree(vertices, faces, faces_1, number_1, node1, number_1);
//         delete faces_1;
//     }
//     else{
//         delete node1;
//         root->node_1= nullptr;
//     }
//  if ((number_2 < previous_faces)&&(number_2>0)){
//         int* faces_2 = new int [3*number_2];
//         for(int i=0; i<number_2;i++){
//             faces_2[i] = node2->faces_in_node[i];
//         }
//        node2->number_of_node_faces = number_2;
//         build_tree(vertices, faces, faces_2, number_2, node2, number_2);
//         delete faces_2;
//     }
//     else{
//         delete node2;
//         root->node_2= nullptr;
//     }
//      if ((number_3 < previous_faces)&&(number_3>0)){
//         int* faces_3 = new int [3*number_3];
//         for(int i=0; i<number_3;i++){
//             faces_3[i] = node3->faces_in_node[i];
//         }
//        node3->number_of_node_faces = number_3;
//         build_tree(vertices, faces, faces_3, number_3, node3, number_3);
//         delete faces_3;
//     }
//     else{
//         delete node3;
//         root->node_3= nullptr;
//     }
//      if ((number_4 < previous_faces)&&(number_4>0)){
//         int* faces_4 = new int [3*number_4];
//         for(int i=0; i<number_4;i++){
//             faces_4[i] = node4->faces_in_node[i];
//         }
//        node4->number_of_node_faces = number_4;
//         build_tree(vertices, faces, faces_4, number_4, node4, number_4);
//         delete faces_4;
//     }
//     else{
//         delete node4;
//         root->node_4= nullptr;
//     }
//      if ((number_5 < previous_faces)&&(number_5>0)){
//         int* faces_5 = new int [3*number_5];
//         for(int i=0; i<number_5;i++){
//             faces_5[i] = node5->faces_in_node[i];
//         }
//        node5->number_of_node_faces = number_5;
//         build_tree(vertices, faces, faces_5, number_5, node5, number_5);
//         delete faces_5;
//     }
//     else{
//         delete node5;
//         root->node_5= nullptr;
//     }
//      if ((number_6 < previous_faces)&&(number_6>0)){
//         int* faces_6 = new int [3*number_6];
//         for(int i=0; i<number_6;i++){
//             faces_6[i] = node6->faces_in_node[i];
//         }
//        node6->number_of_node_faces = number_6;
//         build_tree(vertices, faces, faces_6, number_6, node6, number_6);
//         delete faces_6;
//     }
//     else{
//         delete node6;
//         root->node_6= nullptr;
//     }
//      if ((number_7 < previous_faces)&&(number_7>0)){
//         int* faces_7 = new int [3*number_7];
//         for(int i=0; i<number_7;i++){
//             faces_7[i] = node7->faces_in_node[i];
//         }
//        node7->number_of_node_faces = number_7;
//         build_tree(vertices, faces, faces_7, number_7, node7, number_7);
//         delete faces_7;
//     }
//     else{
//         delete node7;
//         root->node_7= nullptr;
//     }
//     if ((number_8 < previous_faces)&&(number_8>0)){
//         int* faces_8 = new int [3*number_8];
//         for(int i=0; i<number_8;i++){
//             faces_8[i] = node8->faces_in_node[i];
//         }
//         node8->number_of_node_faces = number_8;
//         build_tree(vertices, faces, faces_8, number_8, node8, number_8);
//         delete faces_8;
//     }
//     else{
//         delete node8;
//         root->node_8= nullptr;
//     }
// }

// void search_tree_8::traverse_tree(search_tree_8*root, vector3 eye, vector3 d, std::vector<float> *output){
//     Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
//     if(((root->node_1==nullptr))&&((root->node_2==nullptr))&&((root->node_3==nullptr))&&((root->node_4==nullptr))&&((root->node_5==nullptr))&&((root->node_6==nullptr))&&((root->node_7==nullptr))&&((root->node_8==nullptr))){
//         if((B_root.ray_box_intersection(eye, d)==1)){        
//             for (int i = 0; i<root->number_of_node_faces; i++){
//                 (*output).push_back( root->faces_in_node[i]);
//             }         
//         }   
//     }
//      if((root->node_1!=nullptr)){
//          traverse_tree(root->node_1, eye, d, output);
//      }
//      if (root->node_2!=nullptr){
//         traverse_tree(root->node_2, eye, d, output);
//      }
//      if (root->node_3!=nullptr){
//         traverse_tree(root->node_3, eye, d, output);
//      }
//      if ((root->node_4!=nullptr)){
//         traverse_tree(root->node_4, eye, d, output);
//      }
//      if ((root->node_5!=nullptr)){
//         traverse_tree(root->node_5, eye, d, output);
//      }
//      if((root->node_6!=nullptr)){
//         traverse_tree(root->node_6, eye, d, output);
//      }
//      if ((root->node_7!=nullptr)){
//         traverse_tree(root->node_7, eye, d, output);
//      }
//      if ((root->node_8!=nullptr)){
//         traverse_tree(root->node_8, eye, d, output);
//      }  
// } 