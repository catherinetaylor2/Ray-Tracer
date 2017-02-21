#include <iostream>
#include <cmath>
#include"light.hpp"
#include"vec3.hpp"

using namespace std;

Light::Light(int x, int y, int z){
    light_x=x;
    light_y=y;
    light_z=z;
}
vector3 Light::get_position(void){
    vector3 V(light_x, light_y, light_z);
    return V;
}
vector3 Light::get_light_direction(vector3 point){
    vector3 V = Light::get_position();
    vector3 l = V.vec_add(V, V.vec_scal_mult(-1,point));
            l.normalize();
            return l;
}