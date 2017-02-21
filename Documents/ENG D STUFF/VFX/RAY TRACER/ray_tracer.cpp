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

// initial inputs
    sphere sphere1(0,0,0,1,RED);
    sphere1.set_lighting_constants(0.6, 0.7*255, 0.1, 600);
    vector3 centre(sphere1.get_centre_x(),sphere1.get_centre_y(),sphere1.get_centre_z());
    
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
    double D, DD, Red_term, Green_term, Blue_term;
    for (int x = 0; x<3*myscene.get_x_res()*myscene.get_y_res(); x+=3){
        int i, j;
        i=(x/(3))%(myscene.get_x_res());
        j=(x/(3))/(myscene.get_x_res());
        vector3 s = C.vec_add3(L, C.vec_scal_mult(-1*i*ratio,u), C.vec_scal_mult(-1*j*ratio,v) );
        vector3 d(s.get_x()-eye.get_x(),s.get_y()-eye.get_y(),s.get_z()-eye.get_z());
        d.normalize();

        float t = sphere1.Sphere_ray_intersection( eye, d);
        if (t != 0){
            vector3 point = d.vec_add(eye, d.vec_scal_mult(t,d)); 
            vector3 normal=sphere1.find_normal(point);   
            vector3 l = sun.get_light_direction(point);
            D = myscene.DiffuseValue(normal, l);
            DD = myscene.SpecularValue(normal,l,d);

            Red_term = (sun.get_light_intensity())*(sphere1.get_DiffuseCoeff()*D+sphere1.get_AmbientCoeff())*(sphere1.get_colour()).get_x()+pow(DD,sphere1.get_SpecularPower())*sphere1.get_SpecularCoeff();
            Green_term =(sun.get_light_intensity())*(sphere1.get_DiffuseCoeff()*D+sphere1.get_AmbientCoeff())*(sphere1.get_colour()).get_y()+pow(DD,sphere1.get_SpecularPower())*sphere1.get_SpecularCoeff();
            Blue_term =(sun.get_light_intensity())*(sphere1.get_DiffuseCoeff()*D+sphere1.get_AmbientCoeff())*(sphere1.get_colour()).get_z()+pow(DD,sphere1.get_SpecularPower())*sphere1.get_SpecularCoeff();
           
            if (Red_term > 255){
                Red_term =255;
            }
            if(Red_term < 0){
                cout<<"This should never happen \n";
                break;
            }
            if (Blue_term>255){
                Blue_term=255;
            }
            if(Blue_term < 0){
                cout<<"This should never happen \n";
                break;
            }
            if (Green_term >255){
                Green_term = 255;
            }
             if(Green_term < 0){
                cout<<"This should never happen \n";
                break;
            }
            img[x] = Red_term;
            img[x+1]=Green_term;
            img[x+2]=Blue_term;    
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