#include <cstdlib>
#include <iostream>
#include <cmath>
#include"vec3.hpp"

vector3::vector3(float x, float y, float z){
    x_val=x;
    y_val=y;
    z_val=z;
}
float vector3::get_x(void){
    return x_val;
}
float vector3::get_y(void){
    return y_val;
}
float vector3::get_z(void){
    return z_val;
}
void vector3::setValue(int x, int y, int z){
    x_val=x;
    y_val=y;
    z_val=z;
}
void vector3::normalize(void){
    float sum = sqrt(x_val*x_val + y_val*y_val + z_val*z_val);
    x_val/= sum;
    y_val /= sum;
    z_val /=sum;
}