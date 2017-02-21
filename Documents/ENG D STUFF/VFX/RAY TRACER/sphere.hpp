#ifndef sphere_hpp
#define sphere_hpp
#include<iostream>
#include"vec3.hpp"

class sphere{
    public:
        sphere(int sphere_x, int sphere_y, int sphere_z, int sphere_radius, const int* sphere_colour);
        int get_x_coord(void);
        int get_y_coord(void);
        int get_z_coord(void);
        int get_radius(void);
        int get_centre_x(void);
        int get_centre_y(void);
        int get_centre_z(void);
        vector3 get_colour(void);
        vector3 find_normal(vector3 point);
        float Sphere_ray_intersection(vector3 ray_point, vector3 ray_direction);
    private:
        int centre_x;
        int centre_y;
        int centre_z;
        int radius;
        int colour_x;
        int colour_y;
        int colour_z;
};
#endif