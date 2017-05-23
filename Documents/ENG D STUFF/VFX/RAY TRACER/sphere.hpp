#ifndef sphere_hpp
#define sphere_hpp

#include <iostream>
#include <vector>
#include "vec3.hpp"
#include "light.hpp"
#include "scene.hpp"

class triangle{
    public:
        vector3 get_triangle_normal(void);
        triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z, const int* sphere_colour);
        void get_vertex(std::vector<float> *vertex, int vertex_number);
        void get_colour(std::vector<int>*tri_colour);
        float ray_triangle_intersection(Ray R);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        vector3 determine_colour(vector3 point, vector3 light_direction, Ray R, Light source, vector3 normal, scene myscene, int shadow, float* colours);
    private:
        float point_D;
        std::vector<int> colour;
        std::vector<float> lighting_coefficients, vertex1, vertex2, vertex3, normal;
};

#endif