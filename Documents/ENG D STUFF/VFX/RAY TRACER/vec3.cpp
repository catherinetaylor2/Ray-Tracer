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
float vector3::dotproduct(vector3 vec1, vector3 vec2){
    return vec1.get_x()*vec2.get_x()+vec1.get_y()*vec2.get_y()+vec1.get_z()*vec2.get_z();
}
vector3 vector3::crossproduct(vector3 u, vector3 v){
    float i,j,k;
    i = u.get_y()*v.get_z() - u.get_z()*v.get_y();
    j = u.get_z()*v.get_x() - u.get_x()*v.get_z();
    k = u.get_x()*v.get_y() - u.get_y()*v.get_x();
    vector3 vec(i, j, k);
    return vec;
}
vector3 vector3::vec_add(vector3 v1, vector3 v2){
    float x,y,z;
    x = v1.get_x()+v2.get_x();
    y=v1.get_y()+v2.get_y();
    z=v1.get_z()+v2.get_z();
    vector3 vec(x,y,z);
    return vec;
}
vector3 vector3::vec_add3(vector3 v1, vector3 v2, vector3 v3){
float x,y,z;
    x = v1.get_x()+v2.get_x()+v3.get_x();
    y=v1.get_y()+v2.get_y()+v3.get_y();
    z=v1.get_z()+v2.get_z()+v3.get_z();
    vector3 vec(x,y,z);
    return vec;
}
vector3 vector3::vec_scal_mult(float c, vector3 v){
    float x,y,z;
    x = c*v.get_x();
    y=c*v.get_y();
    z=c*v.get_z();
    vector3 vec(x,y,z);
    return vec;
}
void vector3::normalize(void){
    float sum = sqrt(x_val*x_val + y_val*y_val + z_val*z_val);
    x_val/= sum;
    y_val /= sum;
    z_val /=sum;
}