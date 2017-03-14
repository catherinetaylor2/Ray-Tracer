#include <cstdlib>
#include <iostream>
#include <cmath>
#include"scene.hpp"

#define PI 3.141592654f

scene::scene(int x, int y, int fov, int d){
    x_res = x;
    y_res= y;
    height = 2*(float)d*tan((float)fov/360.0f *PI/2.0f );
    width = ((float)x/(float)y)*height;
    distance_to_image = d;
}
int scene::get_x_res(void){
    return x_res;
}
int scene::get_y_res(void){
    return y_res;
}
float scene::get_width(void){
    return width;
}
float scene::get_height(void){
    return height;
}
float scene::get_distance_to_image(void){
    return distance_to_image;
}
double scene::DiffuseValue( vector3 normal, vector3 light_direction){
    if (normal.dotproduct(normal,light_direction)>0){        
        return normal.dotproduct(normal,light_direction);
    }
    else{
        return 0;
    }
}
double scene::SpecularValue(vector3 normal, vector3 light_direction, vector3 ray_direction){
    vector3 H =normal.vec_add(light_direction, normal.vec_scal_mult(-1,ray_direction));
    H.normalize();
    if (normal.dotproduct(normal, H)<0){
        return 0;
    }
    else{
        return normal.dotproduct(normal, H);
    }   
}
