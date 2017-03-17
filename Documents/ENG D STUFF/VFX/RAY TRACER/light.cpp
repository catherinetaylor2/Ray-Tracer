#include <iostream>
#include <cmath>
#include"light.hpp"
#include"vec3.hpp"


Light::Light(float x, float y, float z, float I){
    light_x=x;
    light_y=y;
    light_z=z;
    light_intensity=I;
}
float Light::get_light_intensity(void){
    return light_intensity;
}
vector3 Light::get_position(void){
    vector3 V(light_x, light_y, light_z);
    return V;
}
vector3 Light::get_light_direction(vector3 point){
    vector3 V = Light::get_position();
    vector3 l =vector3::vec_add(V, vector3::vec_scal_mult(-1,point));
    l.normalize();
    return l;
}