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
class plane{
    public:
        vector3 get_plane_normal(void);
    private:
        float normal_x;
        float normal_y;
        float normal_z;

};
class triangle{
    public:
        vector3 get_triangle_normal(vector3 V1, vector3 V2, vector3 V3);
        triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z );
        vector3 get_vertex1(void);
        vector3 get_vertex2(void);
        vector3 get_vertex3(void);
        float ray_plane_intersection(vector3 ray_point, vector3 ray_direction);
        float ray_triangle_intersection(vector3 ray_point, vector3 ray_direction);
        vector3 barycentric_coords(vector3 intersection_point);
    private:
       float vertex1_x;
       float vertex1_y;
       float vertex1_z;
       float vertex2_x;
       float vertex2_y;
       float vertex2_z;
       float vertex3_x;
       float vertex3_y;
       float vertex3_z;
       float normal_x;
       float normal_y;
       float normal_z;
       float point_D;
};
#endif