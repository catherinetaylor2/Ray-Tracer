#ifndef scene_hpp
#define scene_hpp

#include <iostream>
#include "vec3.hpp"

class scene{
    public:
        scene(int x, int y, int fov, float d);
        int get_x_res(void){
            return x_res;
        }
        int get_y_res(void){
            return y_res;
        }
        float get_width(void){
            return width;
        }
        float get_height(void){
            return height;
        }
        float get_distance_to_image(void){
            return distance_to_image;
        }
        float DiffuseValue( vector3 normal, vector3 light_direction);
        float scene::SpecularValue(vector3 normal, vector3 light_direction, vector3 ray_direction);
    private:
        int x_res;
        int y_res;
        float width;
        float height;
        float distance_to_image;
};
#endif