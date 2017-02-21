#ifndef light_hpp
#define light_hpp
#include<iostream>
#include"vec3.hpp"

class Light{
    public:
    Light(int x, int y, int z, float I);
    vector3 get_light_direction(vector3 point);
    vector3 get_position(void);
    float get_light_intensity(void);
    private:
        int light_x;
        int light_y;
        int light_z;
        float light_intensity;

};
#endif