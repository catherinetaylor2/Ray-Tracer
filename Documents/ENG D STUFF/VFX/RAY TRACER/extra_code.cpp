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