#ifndef readObj_hpp
#define readObj_hpp
#include <stdio.h>
#include <string>

class ObjFile{
    public:
        ObjFile(const char* name);
        float* get_vertices(void);
        float* get_normals(void);
        int* get_faceN(void);
        int* get_faceV(void);
        int get_number_of_faces(void);
    private:
		std::string fn;
        int number_of_normals, number_of_vertices, number_of_faces;
};
class ObjFile_novt{
    public:
        ObjFile_novt(const char* name);
        float* get_vertices(void);
        float* get_normals(void);
        int* get_faceN(void);
        int* get_faceV(void);
        int get_number_of_faces(void);
    private:
		std::string fn;
        int number_of_normals, number_of_vertices, number_of_faces;
};

#endif