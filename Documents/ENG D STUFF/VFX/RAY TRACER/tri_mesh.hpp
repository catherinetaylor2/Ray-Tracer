#ifndef tri_mesh_hpp
#define tri_mesh_pp

#include "readObj.hpp"
#include "search_tree.hpp"

class mesh{
    public:
        mesh(ObjFile input_mesh);
        ~mesh();
        int get_number_of_faces(void){
            return number_of_faces;
        }
        int get_number_of_vertices(void){
            return number_of_vertices;
        }
    private:
        float* vertices = nullptr;
        float*normals = nullptr;
        float* textures = nullptr;
        int* face_vertices = nullptr;
        int* face_normals = nullptr;
        int* face_textures = nullptr;
        int number_of_faces;
        int number_of_vertices;
        search_tree* root;
        std::vector<search_tree*> leaf_nodes;
};

#endif