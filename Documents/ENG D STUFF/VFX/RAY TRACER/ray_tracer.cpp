#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "light.hpp"

using namespace std;

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};
const int PURPLE[]= {255,0,255};
const int YELLOW[]={255,255,0};
const int GREY []={200,200,200};

int main(){

 //initial inputs
    sphere sphere1(0,0,0,1,RED);
      sphere sphere2(-1,0,0,1,BLUE);
  // triangle triangle1(0,3,2,-5,0,2,4,0,2,BLUE);
   sphere1.set_lighting_constants(0.6, 0.7*255, 0.1, 600);
    //   sphere2.set_lighting_constants(0.6, 0, 0.2, 600);
    //triangle1.set_lighting_constants(0.6, 0.5*255, 0.1, 800);
    
   plane plane1(0, -1, 0 , 2 ,3, 20, 2,-4, -10,GREY);
   plane1.set_lighting_constants(0.4, 0.8*255,0.1,300);

   vector3 eye(0,0,-8);
    vector3 lookup(0,1,-8);
    vector3 lookat(0,0,1);

    Light sun(4,3,-5,1);
    vector3 light = sun.get_position();

    scene myscene(1000,1000,90,3);
    float d = myscene.get_distance_to_image();
    
//set up eye coord system
    vector3 w = eye.vec_add(eye, eye.vec_scal_mult(-1, lookat));
    w.normalize();
    vector3 u = w.crossproduct(lookup, w);
    u.normalize();
    vector3 v = w.crossproduct(w,u); 
    vector3 C = w.vec_add(eye,w.vec_scal_mult(-d,w)); 
    
    float half_width= (float)myscene.get_width()/2.0f, half_height = (float)myscene.get_height()/2.0f;
    vector3 L = C.vec_add3(C, C.vec_scal_mult(half_width,u), C.vec_scal_mult(half_height,v) );
    float ratio = (myscene.get_width())/((float)myscene.get_x_res());
   
    unsigned char *img = new unsigned char[3*myscene.get_x_res()*myscene.get_y_res()];
   
    for (int x = 0; x<3*myscene.get_x_res()*myscene.get_y_res(); x+=3){
        int i, j;
        i=(x/(3))%(myscene.get_x_res());
        j=(x/(3))/(myscene.get_x_res());
        vector3 s = C.vec_add3(L, C.vec_scal_mult(-1*i*ratio,u), C.vec_scal_mult(-1*j*ratio,v) );
        vector3 d(s.get_x()-eye.get_x(),s.get_y()-eye.get_y(),s.get_z()-eye.get_z());
        d.normalize();

        float t1 = sphere1.Sphere_ray_intersection( eye, d);
       float t2 = abs(plane1.ray_plane_intersection(eye,d)*(plane1.ray_plane_intersection(eye,d)>0));
      
         // float t2 = sphere2.Sphere_ray_intersection( eye, d);
       //float t2 = triangle1.ray_triangle_intersection(eye,d);
        if ((t1 != 0)&&(t2!=0)){            
            if (t1<t2){
         
                float t=t1;
                vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
                vector3 l = sun.get_light_direction(point); 
                vector3 normal=sphere1.find_normal(point); 
               
                vector3 RGB = sphere1.determine_colour(point, l, d, sun, normal, myscene,1);



                img[x] = RGB.get_x();
                img[x+1]=RGB.get_y();
                img[x+2]=RGB.get_z();  
             }
            else if(t2<t1){
                float t=t2;
                vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
                vector3 l = sun.get_light_direction(point); 

                 vector3 normal=plane1.get_plane_normal(); 

                // vector3 normal=sphere2.find_normal(point); 
                // vector3 RGB = sphere2.determine_colour(point, l, d, sun, normal, myscene,1);

                // vector3 normal=triangle1.get_triangle_normal(triangle1.get_vertex1(), triangle1.get_vertex2(), triangle1.get_vertex3());  
                // vector3 RGB = triangle1.determine_colour(point, l, d, sun, normal, myscene,1);

               


 vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,1);
                                
                img[x] = RGB.get_x();
                img[x+1]=RGB.get_y();
                img[x+2]=RGB.get_z(); 


   
            }
       }
        else if ((t1 != 0)&&(t2==0)){
            float t=t1;
            vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
            vector3 l = sun.get_light_direction(point); 
            vector3 normal=sphere1.find_normal(point); 

        float ss = plane1.ray_plane_intersection(point,l);   
//float ss = sphere2.Sphere_ray_intersection( point, l);
         // float ss = triangle1.ray_triangle_intersection( point, l);
            int s = (ss<=0);
           vector3 RGB = sphere1.determine_colour(point, l, d, sun, normal, myscene,s);
             
            img[x] = RGB.get_x();
            img[x+1]=RGB.get_y();
            img[x+2]=RGB.get_z();  
        }
        else if ((t1 == 0)&&(t2!=0)){
            float t=t2;
            vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
            vector3 l = sun.get_light_direction(point); 
           //vector3 normal=triangle1.get_triangle_normal(triangle1.get_vertex1(), triangle1.get_vertex2(), triangle1.get_vertex3());  
            // vector3 normal=sphere2.find_normal(point); 

             
             vector3 normal=plane1.get_plane_normal(); 
               

            float ss = sphere1.Sphere_ray_intersection( point, l);
            int s = (ss<=0);
         // vector3 RGB = triangle1.determine_colour(point, l, d, sun, normal, myscene,s);
             //vector3 RGB = sphere2.determine_colour(point, l, d, sun, normal, myscene,s);

              //multiple refelections
                vector3 R=normal.vec_scal_mult(2*normal.dotproduct(normal, normal.vec_scal_mult(-1,d)),normal);
                vector3 H = R.vec_add(R, normal.vec_scal_mult(1,d));
             
                H.normalize();
                float t3 = sphere1.Sphere_ray_intersection( point, H);
              
             
                if (t3!=0){
                         vector3 point2 = d.vec_add(point, d.vec_scal_mult(t3,H));
                        //  cout<<"px "<<point.get_x()<<" ";
                        //   cout<<"py "<<point.get_y()<<" ";
                        //    cout<<"pz "<<point.get_z()<<"\n";
          vector3 l2 = sun.get_light_direction(point2); 
          vector3 normal2=sphere1.find_normal(point2); 
                               vector3 RGB2 = sphere1.determine_colour(point2, l2, d, sun, normal2, myscene,s);

                               vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,s);
                                float R,G,B;
                                R=  RGB2.get_x()+RGB.get_x();
                                if (R>255){
                                    R=255;
                                }
                                G = RGB2.get_y()+RGB.get_y();
                                if (G>255){
                                    G=255;
                                }
                               B=RGB2.get_z()+RGB.get_z();  
                               if(B>255){
                                   B=255;
                               }
                img[x] = R;
                img[x+1]= G;
                img[x+2]= B;

             

                }
                else if (t3==0){
                                vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,s);
                                
                img[x] = RGB.get_x();
                img[x+1]=RGB.get_y();
                img[x+2]=RGB.get_z(); 

                }
            
            //  vector3 RGB = plane1.determine_colour(point, l, d, sun, normal, myscene,s);
            // img[x] = RGB.get_x();
            // img[x+1]=RGB.get_y();
            // img[x+2]=RGB.get_z();  
        }
        else{
            img[x]=0;
            img[x+1]=0;
            img[x+2]=0; 
        }
    }
  
    ofstream my_image;
    my_image.open("test.ppm", ios::out| ios::binary);
    my_image<<"P6 \n" 
    <<myscene.get_x_res()<<" "
    <<myscene.get_y_res()<<"\n"
    <<255<<"\n";
    for (int i=0; i<3*myscene.get_x_res()*myscene.get_y_res(); i++){
        my_image << img[i];
        
    }
    my_image.close();
    return 0;
}