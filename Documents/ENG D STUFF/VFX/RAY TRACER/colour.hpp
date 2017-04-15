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
       static vector3 phong_normal(int triangle, float* vertices, float*normals, int*face, int*face_normals,  float* areas, float*edges, vector3 point, vector3 eye, float** barycentric);
       static vector3 intersection_colour(vector3 direction, vector3 camera_origin, search_tree* root,  float* vertices, float*normals,  int*face, int*face_normals, int* face_texture, float *textures, float* areas, float*edges, const int* tri_colour, Light sun, scene myscene, unsigned char* data, int texture_width, int texture_height);
       static void anti_aliasing(std::vector<vector3> scene_pos, search_tree* root,  std::vector<float*> mesh_data, std::vector<int*> mesh_data_i,  const int* tri_colour, Light sun, scene myscene, std::vector<vector3> *colours, vector3 L, float* ijit, unsigned char *data, int* texture_data);
    private:

};

#endif