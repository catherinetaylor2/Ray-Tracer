#ifndef triangle_hpp
#define triangle_hpp

#include <iostream>
#include <vector>
#include "vec3.hpp"
#include "light.hpp"
#include "scene.hpp"

class triangle{
    public:
        triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z, const int* sphere_colour);
        vector3 get_triangle_normal(void){
            return normal;
        }
        vector3 get_colour(void){
            return colour;
        }
        float ray_triangle_intersection(Ray R);
        void set_lighting_constants(float DC, float SC, float AC, float SP);
        vector3 determine_colour(vector3 point, vector3 light_direction, Ray R, Light source, vector3 normal, scene myscene, int shadow, float* colours);
    private:
        float point_D;
        std::vector<float> lighting_coefficients;
        vector3 V1;
        vector3 V2;
        vector3 V3;
        vector3 normal;
        vector3 colour;
};

#endif