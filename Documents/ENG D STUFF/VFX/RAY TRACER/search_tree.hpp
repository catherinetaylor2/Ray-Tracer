#ifndef search_tree_hpp
#define search_tree_hpp
#include<iostream>

class search_tree{
    public:
        search_tree *left_node;
        search_tree *right_node;

        int*faces_in_node;
        float parameters [6];
        static void build_tree(float* vertices, int* faces, int* node_faces, int number_of_faces, search_tree* root, int previous_faces);
    private:
};

#endif