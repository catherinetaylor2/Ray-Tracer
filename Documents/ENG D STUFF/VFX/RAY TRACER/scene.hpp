#ifndef scene_hpp
#define scene_hpp
#include<iostream>

class scene{
    public:
    scene(int x, int y, int fov, int d);
    int get_x_res(void);
    int get_y_res(void);
    float get_width(void);
    float get_height(void);
    private:
        int x_res;
        int y_res;
        float width;
        float height;
};
#endif