#ifndef colour_hpp
#define colour_hpp
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include"vec3.hpp"
#include"sphere.hpp"
#include "search_tree.hpp"
#include "light.hpp"
#include "scene.hpp"

#define infinity FLT_MAX

class TriangleColour{
    public:
       static void phong_areas(int*faces, int*face_normals, float*normals, float*vertices, float* areas, float *edges, int number_of_faces);
       static int shadows(int* triangle_intersections, int*faces, float*vertices, vector3 point, vector3 l, const int* sphere_colour);
       static vector3 phong_normal(int triangle, float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, vector3 point, vector3 eye);
       static vector3 intersection_colour(vector3 direction, vector3 camera_origin, search_tree* root,  float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, const int* tri_colour, Light sun, scene myscene, std::vector<int> output);
       static void anti_aliasing(float ratio, vector3 u, vector3 v, vector3 camera_origin, search_tree* root,  float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, const int* tri_colour, Light sun, scene myscene, std::vector<vector3> *colours, vector3 L, float i, float j, int it);
    private:

};

#endif