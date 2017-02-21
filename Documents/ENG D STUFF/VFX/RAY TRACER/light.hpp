#ifndef light_hpp
#define light_hpp
#include<iostream>
#include"vec3.hpp"

class Light{
    public:
    Light(int x, int y, int z);
    vector3 get_light_direction(vector3 point);
    vector3 get_position(void);
    private:
        int DiffuseCoeff;
        int SpecularCoeff;
        int AmbientCoeff;
        int SpecularPower;
        int light_x;
        int light_y;
        int light_z;

};
#endif