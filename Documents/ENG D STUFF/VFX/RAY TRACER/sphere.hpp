#ifndef sphere_hpp
#define sphere_hpp
#include<iostream>
#include"vec3.hpp"

class sphere{
    public:
        sphere(int sphere_x, int sphere_y, int sphere_z, int sphere_radius, const int* sphere_colour);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        int get_x_coord(void);
        int get_y_coord(void);
        int get_z_coord(void);
        int get_radius(void);
        int get_centre_x(void);
        int get_centre_y(void);
        int get_centre_z(void);
        float get_DiffuseCoeff(void);
        float get_SpecularCoeff(void);
        float get_AmbientCoeff(void);
        float get_SpecularPower(void);
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
        float DiffuseCoeff;
        float SpecularCoeff;
        float AmbientCoeff;
        float SpecularPower;
};
#endif