#ifndef light_hpp
#define light_hpp
#include<iostream>
#include"vec3.hpp"

class Light{
    public:
    Light(float x, float y, float z, float I);
    vector3 get_light_direction(vector3 point);
    vector3 get_position(void);
    float get_light_intensity(void);
    private:
        float light_x, light_y, light_z;
        float light_intensity;

};
#endif