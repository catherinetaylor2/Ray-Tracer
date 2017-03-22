#ifndef sphere_hpp
#define sphere_hpp
#include<iostream>
#include <vector>
#include"vec3.hpp"
#include"light.hpp"
#include"scene.hpp"


class sphere{
    public:
        sphere(int sphere_x, int sphere_y, int sphere_z, int sphere_radius, const int* sphere_colour);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        void get_centre(std::vector<int>*sphere_centre);
        void get_colour(std::vector<int>*sphere_colour);
        void get_lighting_coefficients(std::vector<float>*sphere_coefficients);
        int get_radius(void);
        vector3 find_normal(vector3 point);
        float Sphere_ray_intersection(vector3 ray_point, vector3 ray_direction);
        vector3 determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow);
    private:
        int radius;
        std::vector<int> colour, centre;
        std::vector<float> lighting_coefficients;
};
class plane{
    public:
        plane(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z, const int* plane_colour);
        void get_plane_normal(std::vector<float>*plane_normal);
        float ray_plane_intersection(vector3 ray_point, vector3 ray_direction);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        vector3 determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow);
    private:
        float point_D;
        std::vector<int> colour;
        std::vector<float> normal, lighting_coefficients;
};
class triangle{
    public:
        vector3 get_triangle_normal(void);
        triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z, const int* sphere_colour);
        void get_vertex(std::vector<float> *vertex, int vertex_number);
        void get_colour(std::vector<int>*tri_colour);
        float ray_triangle_intersection(vector3 ray_point, vector3 ray_direction);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        vector3 determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow);
    private:
        float point_D;
        std::vector<int> colour;
        std::vector<float> lighting_coefficients, vertex1, vertex2, vertex3, normal;
};
#endif