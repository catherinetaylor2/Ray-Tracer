#ifndef colour_hpp
#define colour_hpp
#include<iostream>
#include"vec3.hpp"
#include"sphere.hpp"

class TriangleColour{
    public:
       static void phong_areas(int*faces, int*face_normals, float*normals, float*vertices, float* areas, float *edges, int number_of_faces);
       static int shadows(float* triangle_intersections, int*faces, float*vertices, vector3 point, vector3 l, const int* sphere_colour);
       static vector3 phong_normal(int triangle, float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, vector3 point);
    private:

};

#endif