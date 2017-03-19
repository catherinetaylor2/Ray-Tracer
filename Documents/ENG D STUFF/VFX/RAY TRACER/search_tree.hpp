#ifndef search_tree_hpp
#define search_tree_hpp
#include<iostream>
#include "vec3.hpp"
#include <vector>

class search_tree{
    public:
        search_tree *left_node;
        search_tree *right_node;

        int*faces_in_node;
        float parameters [6];
        int number_of_node_faces;
        static void build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree* root, int previous_faces);
        static void build_tree_leaves(float* vertices, int* faces, std::vector<search_tree*> leaf_nodes, search_tree**root );
        static void traverse_tree(search_tree*root, vector3 eye, vector3 d, std::vector<float> *output);
        static std::vector<search_tree*> leaf_nodes(float* vertices, int*faces, int number_of_faces);
    private:
};
class search_tree_8{
       public:
            search_tree_8 *node_1;
            search_tree_8 *node_2;
            search_tree_8 *node_3;
            search_tree_8 *node_4;
            search_tree_8 *node_5;
            search_tree_8 *node_6;
            search_tree_8 *node_7;
            search_tree_8 *node_8;

            int*faces_in_node;
            float parameters [6];
            int number_of_node_faces;
            static void build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree_8* root, int previous_faces);
            static void traverse_tree(search_tree_8*root, vector3 eye, vector3 d, std::vector<float> *output);
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