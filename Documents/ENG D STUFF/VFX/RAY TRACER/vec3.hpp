#ifndef vec3_hpp
#define vec3_hpp
#include<iostream>

class vector3{
    public:        
        vector3(float x, float y, float z);
        float get_x(void);
        float get_y(void);
        float get_z(void);
        void normalize(void);
        void setValue(int x, int y, int z);
        static float dotproduct(vector3 v1, vector3 v2);
        static vector3 crossproduct(vector3 v1, vector3 v2);
        static vector3 vec_scal_mult(float c, vector3 v);
        static vector3 vec_add(vector3 v1, vector3 v2);
        static vector3 vec_add3(vector3 v1, vector3 v2, vector3 v3);
    private:    
        float x_val;
        float y_val;
        float z_val;
};
#endif