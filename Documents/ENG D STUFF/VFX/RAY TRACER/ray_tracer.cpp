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

int main(){

 //initial inputs
    sphere sphere1(0,1,-1,1,RED);
    triangle triangle1(0,3,3,-4,0,3,4,0,3,BLUE);
    sphere1.set_lighting_constants(0.6, 0.7*255, 0.1, 600);
    triangle1.set_lighting_constants(0.6, 0.5*255, 0.1, 800);
    
    vector3 eye(0,0,-5);
    vector3 lookup(0,1,-5);
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
        float t2 = triangle1.ray_triangle_intersection(eye,d);
        if ((t1 != 0)&&(t2!=0)){            
            if (t1<t2){
                float t=t1;
                vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
                vector3 l = sun.get_light_direction(point); 
                vector3 normal=sphere1.find_normal(point); 
               
                vector3 RGB = sphere1.determine_colour(point, l, d, sun, normal, myscene);



                img[x] = RGB.get_x();
                img[x+1]=RGB.get_y();
                img[x+2]=RGB.get_z();  
            }
            else if(t2<t1){
                float t=t2;
                vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
                vector3 l = sun.get_light_direction(point); 
                vector3 normal=triangle1.get_triangle_normal(triangle1.get_vertex1(), triangle1.get_vertex2(), triangle1.get_vertex3());  
                vector3 RGB = triangle1.determine_colour(point, l, d, sun, normal, myscene);
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
            vector3 RGB = sphere1.determine_colour(point, l, d, sun, normal, myscene);
            img[x] = RGB.get_x();
            img[x+1]=RGB.get_y();
            img[x+2]=RGB.get_z();  
        }
        else if ((t1 == 0)&&(t2!=0)){
            float t=t2;
            vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d));
            vector3 l = sun.get_light_direction(point); 
            vector3 normal=triangle1.get_triangle_normal(triangle1.get_vertex1(), triangle1.get_vertex2(), triangle1.get_vertex3());  
            vector3 RGB = triangle1.determine_colour(point, l, d, sun, normal, myscene);
            float ss = sphere1.Sphere_ray_intersection( point, l);
            int s = (ss<=0);
             
            img[x] = s*RGB.get_x();
            img[x+1]=s*RGB.get_y();
            img[x+2]=s*RGB.get_z();  
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