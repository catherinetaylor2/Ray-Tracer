#include <cstdlib>
#include <iostream>
#include <cmath>
#include"scene.hpp"

#define PI 3.141592654f

scene::scene(int x, int y, int fov, int d){
    x_res = x;
    y_res= y;
       height = 2*d*tan((float)fov/360.0f *PI/2.0f );
        width = ((float)x/(float)y)*height;
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
