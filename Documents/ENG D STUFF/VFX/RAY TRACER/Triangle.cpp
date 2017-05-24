#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include "Triangle.hpp"
#include "vec3.hpp"
#include "light.hpp"
#include "scene.hpp"

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};

triangle::triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z){
    V1.setValue(v1x, v1y, v1z);
    V2.setValue(v2x, v2y, v2z);
    V3.setValue(v3x, v3y, v3z);
    vector3 N = vector3::crossproduct(vector3::vec_add(V2, vector3::vec_scal_mult(-1, V1)), vector3::vec_add(V3, vector3::vec_scal_mult(-1, V1)));
    N.normalize();
    normal.setValue(N.get_x(), N.get_y(), N.get_z()); 
    point_D = vector3::dotproduct(N, V1);
}

float triangle::ray_triangle_intersection(Ray R){
    float r = vector3::dotproduct(normal, R.get_direction());
    if (fabs(r) < 0.000000001f){
              return 0;
    }
    float t=(point_D - vector3::dotproduct(normal,R.get_origin()) )/r;
    vector3 intersection_point = vector3::vec_add(R.get_origin(), vector3::vec_scal_mult(t,  R.get_direction()));

    if (
    (vector3::dotproduct(vector3::crossproduct(vector3::vec_add(V2, vector3::vec_scal_mult(-1, V1)), vector3::vec_add(intersection_point, vector3::vec_scal_mult(-1, V1))), normal)>=-0.0000001f)&&
    (vector3::dotproduct(vector3::crossproduct(vector3::vec_add(V3, vector3::vec_scal_mult(-1, V2)), vector3::vec_add(intersection_point,vector3::vec_scal_mult(-1, V2))), normal)>=-0.0000001f)&&
    (vector3::dotproduct(vector3::crossproduct(vector3::vec_add(V1, vector3::vec_scal_mult(-1, V3)), vector3::vec_add(intersection_point, vector3::vec_scal_mult(-1, V3))), normal)>=-0.0000001f))
    {
            return t;
    }
    return 0;
}
 void triangle::set_lighting_constants(float DC, float SC, float AC, float SP){
     lighting_coefficients = {DC, SC, AC, SP};
 }

vector3 triangle::determine_colour(vector3 point, vector3 light_direction, Ray R, Light source, vector3 normal, scene myscene, int shadow, float* colours){
    float D, DD, Red_term, Green_term, Blue_term;
    D = myscene.DiffuseValue(normal, light_direction);
    DD = myscene.SpecularValue(normal,light_direction, R.get_direction());
    Red_term = (source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colours[0]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Green_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colours[1]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Blue_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colours[2]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    if (Red_term > 255){
        Red_term =255;
    }
    if (Blue_term>255){
        Blue_term=255;
    }
    if (Green_term >255){
        Green_term = 255;
    }
    if((Green_term < 0)||(Red_term < 0)||(Blue_term < 0)){
        std::cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}