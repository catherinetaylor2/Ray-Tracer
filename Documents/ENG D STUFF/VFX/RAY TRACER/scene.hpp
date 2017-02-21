#ifndef scene_hpp
#define scene_hpp
#include<iostream>
#include"vec3.hpp"

class scene{
    public:
        scene(int x, int y, int fov, int d);
        int get_x_res(void);
        int get_y_res(void);
        float get_width(void);
        float get_height(void);
        float get_distance_to_image(void);
        double DiffuseValue( vector3 normal, vector3 light_direction);
        double scene::SpecularValue(vector3 normal, vector3 light_direction, vector3 ray_direction);
    private:
        int x_res;
        int y_res;
        float width;
        float height;
        int distance_to_image;
};
#endif