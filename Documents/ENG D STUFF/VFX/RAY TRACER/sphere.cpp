#include <cstdlib>
#include <iostream>
#include <cmath>
#include"sphere.hpp"
#include"vec3.hpp"

using namespace std;

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};

sphere::sphere(int sphere_x, int sphere_y, int sphere_z, int sphere_radius,  const int* sphere_colour){
    centre_x = sphere_x;
    centre_y=sphere_y;
    centre_z=sphere_z;
    radius=sphere_radius;
    colour_x=sphere_colour[0];
    colour_y=sphere_colour[1];
    colour_z= sphere_colour[2];
}
vector3 sphere::get_colour(void){
    vector3 colour(colour_x, colour_y, colour_z);
    return colour;
}
int sphere::get_radius(void){
    return radius;
}
int sphere::get_centre_x(void){
    return centre_x;
}
int sphere::get_centre_y(void){
    return centre_y;
}
int sphere::get_centre_z(void){
    return centre_z;
}
vector3 sphere::find_normal(vector3 point){     
    vector3 centre(centre_x, centre_y, centre_z);
    vector3 norm = centre.vec_add(point, centre.vec_scal_mult(-1,centre));
    vector3 normal = centre.vec_scal_mult(2,norm);
    normal.normalize();
    return normal;
}
float sphere::Sphere_ray_intersection(vector3 ray_point, vector3 ray_direction){
    float a,b,c, det ;
    vector3 centre(centre_x, centre_y, centre_z);
    a = centre.dotproduct(ray_direction,ray_direction);
    b=2*(centre.dotproduct(ray_direction,ray_point));
    c=centre.dotproduct(ray_point,ray_point)-radius*radius;
    det = b*b - 4*a*c;
    if (det >= 0){     
        float  t1,t2;
        t1 = (-1*b -sqrt(det))/(2*a);
        t2 = (-1*b +sqrt(det))/(2*a);
        return (t1>t2)*t2 + (t2>t1)*t1;
    }
    return 0;
 }