#include <cstdlib>
#include <iostream>
#include <cmath>
#include "scene.hpp"

#define PI 3.141592654f

scene::scene(int x, int y, int fov, float d){
    x_res = x;
    y_res= y;
    height = 2*(float)d*tan((float)fov/360.0f *PI/2.0f );
    width = ((float)x/(float)y)*height;
    distance_to_image = d;
}
float scene::DiffuseValue( vector3 normal, vector3 light_direction){
    if (vector3::dotproduct(normal,light_direction)>0){        
        return vector3::dotproduct(normal,light_direction);
    }
    else{
        return 0;
    }
}
float scene::SpecularValue(vector3 normal, vector3 light_direction, vector3 ray_direction){
    vector3 H =vector3::vec_add(light_direction, vector3::vec_scal_mult(-1,ray_direction));
    H.normalize();
    if (vector3::dotproduct(normal, H)<0){
        return 0;
    }
    else{
        return vector3::dotproduct(normal, H);
    }   
}
