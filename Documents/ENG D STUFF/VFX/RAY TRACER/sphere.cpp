#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include"sphere.hpp"
#include"vec3.hpp"
#include"light.hpp"
#include"scene.hpp"

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};

sphere::sphere(int sphere_x, int sphere_y, int sphere_z, int sphere_radius,  const int* sphere_colour){
    centre = {sphere_x, sphere_y, sphere_z};
    colour = {sphere_colour[0], sphere_colour[1], sphere_colour[2]};
}
void sphere::get_centre(std::vector<int>*sphere_centre){
    *sphere_centre = centre;
}
void sphere::get_colour(std::vector<int>*sphere_colour){
    *sphere_colour = colour;
}
 void sphere::set_lighting_constants(float DC, float SC, float AC, float SP){
     lighting_coefficients = {DC, SC, AC, SP};
 }
int sphere::get_radius(void){
    return radius;
}
void sphere::get_lighting_coefficients(std::vector<float>*sphere_coefficients){
    *sphere_coefficients = lighting_coefficients;
}
vector3 sphere::find_normal(vector3 point){
    vector3 centre(centre[0], centre[1], centre[2]);
    vector3 norm = vector3::vec_add(point, vector3::vec_scal_mult(-1,centre));
    vector3 normal = vector3::vec_scal_mult(2,norm);
    normal.normalize();
    return normal;
}
float sphere::Sphere_ray_intersection(vector3 ray_point, vector3 ray_direction){
    float a,b,c, det ;
    vector3 centre(centre[0], centre[1], centre[2]);
    a = vector3::dotproduct(ray_direction,ray_direction);
    b=2*(vector3::dotproduct(ray_direction,vector3::vec_add(ray_point, vector3::vec_scal_mult(-1, centre))));
    c=vector3::dotproduct(vector3::vec_add(ray_point, vector3::vec_scal_mult(-1, centre)),vector3::vec_add(ray_point, vector3::vec_scal_mult(-1, centre)))-radius*radius;
    det = b*b - 4*a*c;
    if (det >= 0){
        float  t1,t2;
        t1 = (-1*b -sqrt(det))/(2*a);
        t2 = (-1*b +sqrt(det))/(2*a);
        return (t1>t2)*t2 + (t2>t1)*t1;
    }
    return 0;
 }
vector3 sphere::determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow){
    float D, DD, Red_term, Green_term, Blue_term;
    D = myscene.DiffuseValue(normal, light_direction);
    DD = myscene.SpecularValue(normal,light_direction,ray_direction);

    Red_term = (source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[0]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Green_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[1]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Blue_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[2]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);

    if (Red_term > 255){
        Red_term =255;
    }
    if (Blue_term>255){
        Blue_term=255;
    }
    if (Green_term >255){
        Green_term = 255;
    }
    if((Green_term < 0)|(Red_term < 0)|(Blue_term < 0)){
        std::cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}

triangle::triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z, const int* triangle_colour ){
    vertex1 = {v1x, v1y, v1z};
    vertex2 = {v2x, v2y, v2z};
    vertex3 = {v3x, v3y, v3z};
    vector3 V1(v1x,v1y,v1z);
    vector3 V2(v2x, v2y, v2z);
    vector3 V3(v3x, v3y, v3z);
    vector3 N = vector3::crossproduct(vector3::vec_add(V2, vector3::vec_scal_mult(-1, V1)), vector3::vec_add(V3, vector3::vec_scal_mult(-1, V1)));
    N.normalize();
    normal = {N.get_x(), N.get_y(), N.get_z()}; 
    point_D = vector3::dotproduct(N, V1);
    colour = {triangle_colour[0], triangle_colour[1], triangle_colour[2]};
}
void triangle::get_vertex(std::vector<float>*vertex,  int vertex_number){
    if(vertex_number ==1){
       *vertex = vertex1;
    }
    else if(vertex_number==2){
       *vertex = vertex2;
    }
    else if (vertex_number==3){
      *vertex = vertex3;
    }
    else{
        std::cout<<"Not valid input \n";
    }
}
vector3 triangle::get_triangle_normal(void){
    vector3 N (normal[0], normal[1], normal[2]);
    return N;
}
void triangle::get_colour(std::vector<int>*tri_colour){
   *tri_colour = colour;
}
float triangle::ray_triangle_intersection(vector3 ray_point, vector3 ray_direction){
    vector3 normal(normal[0], normal[1], normal[2]);
    float r = vector3::dotproduct(normal,ray_direction);
    if (fabs(r) < 0.000000001f){
              return 0;
    }
    float t=(point_D - vector3::dotproduct(normal,ray_point) )/r;
    vector3 intersection_point = vector3::vec_add(ray_point, vector3::vec_scal_mult(t, ray_direction));
    vector3 V1(vertex1[0],vertex1[1],vertex1[2]);
    vector3 V2(vertex2[0], vertex2[1], vertex2[2]);
    vector3 V3(vertex3[0], vertex3[1], vertex3[2]);
    if (
    (vector3::dotproduct(vector3::crossproduct(vector3::vec_add(V2, vector3::vec_scal_mult(-1, V1)), vector3::vec_add(intersection_point, vector3::vec_scal_mult(-1, V1))), normal)>=-0.0001f)&&
    (vector3::dotproduct(vector3::crossproduct(vector3::vec_add(V3, vector3::vec_scal_mult(-1, V2)), vector3::vec_add(intersection_point,vector3::vec_scal_mult(-1, V2))), normal)>=-0.0001f)&&
    (vector3::dotproduct(vector3::crossproduct(vector3::vec_add(V1, vector3::vec_scal_mult(-1, V3)), vector3::vec_add(intersection_point, vector3::vec_scal_mult(-1, V3))), normal)>=-0.0001f))
    {
            return t;
    }
    return 0;
}
 void triangle::set_lighting_constants(float DC, float SC, float AC, float SP){
     lighting_coefficients = {DC, SC, AC, SP};
 }

vector3 triangle::determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow){
    float D, DD, Red_term, Green_term, Blue_term;
    D = myscene.DiffuseValue(normal, light_direction);
    DD = myscene.SpecularValue(normal,light_direction,ray_direction);
    Red_term = (source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[0]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Green_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[1]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Blue_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[2]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    if (Red_term > 255){
        Red_term =255;
    }
    if (Blue_term>255){
        Blue_term=255;
    }
    if (Green_term >255){
        Green_term = 255;
    }
    if((Green_term < 0)||(Red_term < 0)||(Blue_term < 0)){
        std::cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}

plane::plane(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z, const int* plane_colour){
    vector3 P(p1x, p1y, p1z);
    vector3 Q(p2x, p2y, p2z);
    vector3 Z(p3x, p3y, p3z);
    vector3 PQ = vector3::vec_add(Q, vector3::vec_scal_mult(-1,P));
    vector3 PZ = vector3::vec_add(Z, vector3::vec_scal_mult(-1,P));
    vector3 N = vector3::crossproduct(PQ, PZ);
    N.normalize();
    normal = {N.get_x(), N.get_y(), N.get_z()};
    point_D = vector3::dotproduct(N,P);
    colour = { plane_colour[0], plane_colour[1], plane_colour[2]};
}
void plane::get_plane_normal(std::vector<float>*plane_normal){
    *plane_normal = normal;
}
 void plane::set_lighting_constants(float DC, float SC, float AC, float SP){
    lighting_coefficients = {DC, SC,AC, SP};
 }
 vector3 plane::determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow){
   float D, DD, Red_term, Green_term, Blue_term;
    D = myscene.DiffuseValue(normal, light_direction);
    DD = myscene.SpecularValue(normal,light_direction,ray_direction);
    Red_term = (source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[0]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Green_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[1]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    Blue_term =(source.get_light_intensity())*((shadow*lighting_coefficients[0]*D+lighting_coefficients[2])*colour[2]+shadow*pow(DD,lighting_coefficients[3])*lighting_coefficients[1]);
    if (Red_term > 255){
        Red_term =255;
    }
    if (Blue_term>255){
        Blue_term=255;
    }
    if (Green_term >255){
        Green_term = 255;
    }
    if((Green_term < 0)|(Red_term < 0)|(Blue_term < 0)){
        std::cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}

float plane::ray_plane_intersection(vector3 ray_point, vector3 ray_direction){
    vector3 normal(normal[0], normal[1], normal[2]);
    normal.normalize();
    if (vector3::dotproduct(normal,ray_direction)!=0){
        return (( point_D- vector3::dotproduct(normal,ray_point))/(vector3::dotproduct(normal,ray_direction)));
    }
    else{
        return 0;
    }
}