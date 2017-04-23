#ifndef scene_hpp
#define scene_hpp
#include<iostream>
#include"vec3.hpp"

class scene{
    public:
        scene(int x, int y, int fov, float d);
        int get_x_res(void);
        int get_y_res(void);
        float get_width(void);
        float get_height(void);
        float get_distance_to_image(void);
        float DiffuseValue( vector3 normal, vector3 light_direction);
        float scene::SpecularValue(vector3 normal, vector3 light_direction, vector3 ray_direction);
    private:
        int x_res, y_res;
        float width, height, distance_to_image;
};
#endif