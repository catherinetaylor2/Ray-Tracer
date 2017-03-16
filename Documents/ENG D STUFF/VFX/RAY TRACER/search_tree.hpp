#ifndef search_tree_hpp
#define search_tree_hpp
#include<iostream>
#include "vec3.hpp"

class search_tree{
    public:
        search_tree *left_node;
        search_tree *right_node;

        int*faces_in_node;
        float parameters [6];
        int number_of_node_faces;
        static void build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree* root, int previous_faces);
        static int* traverse_tree(search_tree*root, vector3 eye, vector3 d);
        static int left_or_right(search_tree*root, vector3 eye, vector3 d);
    private:
};
class Bounding_box{
    public:
        Bounding_box(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);  
       int ray_box_intersection(vector3 ray_point, vector3 ray_direction);    
       float get_tmin(void);
       float get_tmax(void);
    private:
        float parameters [6];
        float tmin;
        float tmax;

};
#endif