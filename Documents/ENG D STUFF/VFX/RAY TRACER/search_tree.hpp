#ifndef search_tree_hpp
#define search_tree_hpp
#include<iostream>

class search_tree{
    public:
        search_tree *left_node;
        search_tree *right_node;
        search_tree();

        int* vertices_in_node;
        float parameters [6];
        static void build_tree(float* vertices, float* node_vertices, int number_of_vertices, search_tree* root, int previous_vertices);
    private:
};

#endif