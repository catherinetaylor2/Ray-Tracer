#ifndef sphere_hpp
#define sphere_hpp
#include<iostream>
#include"vec3.hpp"
#include"light.hpp"
#include"scene.hpp"

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
        vector3 determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow);
    private:
        int centre_x, centre_y, centre_z, radius, colour_x, colour_y, colour_z;
        float DiffuseCoeff, SpecularCoeff, AmbientCoeff, SpecularPower;
};
class plane{
    public:
        vector3 get_plane_normal(void);
    private:
        float normal_x, normal_y,normal_z;

};
class triangle{
    public:
        vector3 get_triangle_normal(vector3 V1, vector3 V2, vector3 V3);
        triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z,const int* sphere_colour );
        vector3 get_vertex1(void);
        vector3 get_vertex2(void);
        vector3 get_vertex3(void);
        vector3 get_colour(void);
         float get_DiffuseCoeff(void);
        float get_SpecularCoeff(void);
        float get_AmbientCoeff(void);
        float get_SpecularPower(void);
        float ray_plane_intersection(vector3 ray_point, vector3 ray_direction);
        float ray_triangle_intersection(vector3 ray_point, vector3 ray_direction);
        vector3 barycentric_coords(vector3 intersection_point);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        vector3 determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow);
    private:
        float vertex1_x, vertex1_y, vertex1_z, vertex2_x, vertex2_y, vertex2_z, vertex3_x, vertex3_y, vertex3_z;
        float normal_x, normal_y, normal_z, point_D;
        float DiffuseCoeff, SpecularCoeff, AmbientCoeff, SpecularPower;
        int colour_x, colour_y, colour_z;
};
#endif