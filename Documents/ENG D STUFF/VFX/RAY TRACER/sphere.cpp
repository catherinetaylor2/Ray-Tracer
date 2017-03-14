#include <cstdlib>
#include <iostream>
#include <cmath>
#include"sphere.hpp"
#include"vec3.hpp"
#include"light.hpp"
#include"scene.hpp"

using namespace std;

const int RED[] = {255,0,0};
const int GREEN[] ={0,255,0};
const int BLUE[] = {0,0,255};

sphere::sphere(int sphere_x, int sphere_y, int sphere_z, int sphere_radius,  const int* sphere_colour){
    centre_x = sphere_x;
    centre_y=sphere_y;
    centre_z=sphere_z;
    radius=sphere_radius;
    colour_x=sphere_colour[0];
    colour_y=sphere_colour[1];
    colour_z= sphere_colour[2];
}
 void sphere::set_lighting_constants(float DC, float SC, float AC, float SP){
    DiffuseCoeff=DC;
    SpecularCoeff=SC;
    AmbientCoeff=AC;
    SpecularPower=SP;
 }
vector3 sphere::get_colour(void){
    vector3 colour(colour_x, colour_y, colour_z);
    return colour;
}
int sphere::get_radius(void){
    return radius;
}
int sphere::get_centre_x(void){
    return centre_x;
}
int sphere::get_centre_y(void){
    return centre_y;
}
int sphere::get_centre_z(void){
    return centre_z;
}
float sphere::get_DiffuseCoeff(void){
    return DiffuseCoeff;
}
float sphere::get_SpecularCoeff(void){
    return SpecularCoeff;
}
float sphere::get_AmbientCoeff(void){
    return AmbientCoeff;
}
float sphere::get_SpecularPower(void){
    return SpecularPower;
}
vector3 sphere::find_normal(vector3 point){
    vector3 centre(centre_x, centre_y, centre_z);
    vector3 norm = centre.vec_add(point, centre.vec_scal_mult(-1,centre));
    vector3 normal = centre.vec_scal_mult(2,norm);
    normal.normalize();
    return normal;
}
float sphere::Sphere_ray_intersection(vector3 ray_point, vector3 ray_direction){
    float a,b,c, det ;
    vector3 centre(centre_x, centre_y, centre_z);
    a = centre.dotproduct(ray_direction,ray_direction);
    b=2*(centre.dotproduct(ray_direction,centre.vec_add(ray_point, centre.vec_scal_mult(-1, centre))));
    c=centre.dotproduct(centre.vec_add(ray_point, centre.vec_scal_mult(-1, centre)),centre.vec_add(ray_point, centre.vec_scal_mult(-1, centre)))-radius*radius;
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

    Red_term = (source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_x+shadow*pow(DD,SpecularPower)*SpecularCoeff);
    Green_term =(source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_y+shadow*pow(DD,SpecularPower)*SpecularCoeff);
    Blue_term =(source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_z+shadow*pow(DD,SpecularPower)*SpecularCoeff);

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
        cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}





triangle::triangle(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float v3x, float v3y, float v3z,const int* sphere_colour ){
    vertex1_x = v1x;
    vertex1_y = v1y;
    vertex1_z = v1z;
    vertex2_x = v2x;
    vertex2_y = v2y;
    vertex2_z = v2z;
    vertex3_x = v3x;
    vertex3_y = v3y;
    vertex3_z = v3z;

    vector3 V1(v1x,v1y,v1z);
    vector3 V2(v2x, v2y, v2z);
    vector3 V3(v3x, v3y, v3z);
    vector3 N = V1.crossproduct(V1.vec_add(V2, V1.vec_scal_mult(-1, V1)), V1.vec_add(V3, V1.vec_scal_mult(-1, V1)));
    N.normalize();
    normal_x = N.get_x();
    normal_y=N.get_y();
    normal_z=N.get_z();
 
    point_D = N.dotproduct(N, V1);
    colour_x=sphere_colour[0];
    colour_y=sphere_colour[1];
    colour_z= sphere_colour[2];
}
 vector3 triangle::get_vertex1(void){
     vector3 V1(vertex1_x,vertex1_y,vertex1_z);
     return V1;
 }
vector3 triangle::get_vertex2(void){
    vector3 V2(vertex2_x, vertex2_y, vertex2_z);
    return V2;
}
vector3 triangle::get_vertex3(void){
    vector3 V3(vertex3_x, vertex3_y, vertex3_z);
    return V3;
}
vector3 triangle::get_triangle_normal(vector3 V1, vector3 V2, vector3 V3){
    vector3 N (normal_x, normal_y, normal_z);
    return N;
}
vector3 triangle::get_colour(void){
    vector3 C(colour_x, colour_y, colour_z);
    return C;
}
float triangle::ray_triangle_intersection(vector3 ray_point, vector3 ray_direction){
     vector3 normal(normal_x, normal_y, normal_z);
     float r = ray_point.dotproduct(normal,ray_direction);

    if (fabs(r) < 0.000000001f){
              return 0;
       }
    float t=(point_D - ray_point.dotproduct(normal,ray_point) )/r;

    vector3 intersection_point = ray_point.vec_add(ray_point, ray_direction.vec_scal_mult(t, ray_direction));
    vector3 V1(vertex1_x,vertex1_y,vertex1_z);
    vector3 V2(vertex2_x, vertex2_y, vertex2_z);
    vector3 V3(vertex3_x, vertex3_y, vertex3_z);

    if (
    (ray_point.dotproduct(V1.crossproduct(V1.vec_add(V2, V1.vec_scal_mult(-1, V1)), V1.vec_add(intersection_point, V1.vec_scal_mult(-1, V1))), normal)>=-0.0001f)&&
    (ray_point.dotproduct(V1.crossproduct(V1.vec_add(V3, V1.vec_scal_mult(-1, V2)), V1.vec_add(intersection_point, V1.vec_scal_mult(-1, V2))), normal)>=-0.0001f)&&
    (ray_point.dotproduct(V1.crossproduct(V1.vec_add(V1, V1.vec_scal_mult(-1, V3)), V1.vec_add(intersection_point, V1.vec_scal_mult(-1, V3))), normal)>=-0.0001f))
    {
            return t;
    }
 return 0;

}
vector3 triangle::barycentric_coords(vector3 intersection_point){
    vector3 normal(normal_x, normal_y, normal_z);
    vector3 V1(vertex1_x,vertex1_y,vertex1_z);
    vector3 V2(vertex2_x, vertex2_y, vertex2_z);
    vector3 V3(vertex3_x, vertex3_y, vertex3_z);
    float a,b,c,d;
    a = V1.dotproduct(V1.crossproduct(V1.vec_add(V1, V1.vec_scal_mult(-1, V2)), V1.vec_add(intersection_point, V1.vec_scal_mult(-1, V2))), normal);
    b = V1.dotproduct(V1.crossproduct(V1.vec_add(V2, V1.vec_scal_mult(-1, V3)), V1.vec_add(intersection_point, V1.vec_scal_mult(-1, V3))), normal);
    c = V1.dotproduct(V1.crossproduct(V1.vec_add(V3, V1.vec_scal_mult(-1, V1)), V1.vec_add(intersection_point, V1.vec_scal_mult(-1, V1))), normal);
    d = V1.dotproduct(V1.crossproduct(V1.vec_add(V2, V1.vec_scal_mult(-1, V1)), V1.vec_add(V3, V1.vec_scal_mult(-1, V1))), normal);
    vector3 B(a/d, b/d, c/d);
    return B;
}
 void triangle::set_lighting_constants(float DC, float SC, float AC, float SP){
    DiffuseCoeff=DC;
    SpecularCoeff=SC;
    AmbientCoeff=AC;
    SpecularPower=SP;
 }
 float triangle::get_DiffuseCoeff(void){
    return DiffuseCoeff;
}
float triangle::get_SpecularCoeff(void){
    return SpecularCoeff;
}
float triangle::get_AmbientCoeff(void){
    return AmbientCoeff;
}
float triangle::get_SpecularPower(void){
    return SpecularPower;
}
vector3 triangle::determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow){

   float D, DD, Red_term, Green_term, Blue_term;
    D = myscene.DiffuseValue(normal, light_direction);
    DD = myscene.SpecularValue(normal,light_direction,ray_direction);
    Red_term = (source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_x+pow(DD,SpecularPower)*SpecularCoeff);
    Green_term =(source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_y+pow(DD,SpecularPower)*SpecularCoeff);
    Blue_term =(source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_z+pow(DD,SpecularPower)*SpecularCoeff);
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
        cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}

// plane::plane(float nx, float ny, float nz, float px, float py, float pz, const int* plane_colour){
//     normal_x = nx;
//     normal_y = ny;
//     normal_z = nz;
//     vector3 normal(nx, ny, nz);
//     vector3 point(px,py,pz);
//     point_D = -1*point.dotproduct(normal,point);
//     cout<<"D "<<point_D<<"\n";
//     colour_x=plane_colour[0];
//     colour_y=plane_colour[1];
//     colour_z= plane_colour[2];
// }
plane::plane(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z, const int* plane_colour){
    vector3 P(p1x, p1y, p1z);
     vector3 Q(p2x, p2y, p2z);
      vector3 Z(p3x, p3y, p3z);
      vector3 PQ = P.vec_add(Q, P.vec_scal_mult(-1,P));
      vector3 PZ = P.vec_add(Z, P.vec_scal_mult(-1,P));
      vector3 N = P.crossproduct(PQ, PZ);
    N.normalize();
          normal_x = N.get_x();
    normal_y = N.get_y();
    normal_z = N.get_z();
    // cout<<"nx "<<normal_x<<"\n";
    // cout<<"ny "<<normal_y<<"\n";
    // cout<<"nz "<<normal_z<<"\n";
    point_D = P.dotproduct(N,P);
        colour_x=plane_colour[0];
    colour_y=plane_colour[1];
    colour_z= plane_colour[2];

}
vector3 plane::get_plane_normal(void){
    vector3 normal(normal_x, normal_y, normal_z);
    normal.normalize();
    return normal;
}
 void plane::set_lighting_constants(float DC, float SC, float AC, float SP){
    DiffuseCoeff=DC;
    SpecularCoeff=SC;
    AmbientCoeff=AC;
    SpecularPower=SP;
 }
 vector3 plane::determine_colour(vector3 point, vector3 light_direction, vector3 ray_direction, Light source, vector3 normal, scene myscene, int shadow){

   float D, DD, Red_term, Green_term, Blue_term;
    D = myscene.DiffuseValue(normal, light_direction);
    DD = myscene.SpecularValue(normal,light_direction,ray_direction);
    Red_term = (source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_x+pow(DD,SpecularPower)*SpecularCoeff);
    Green_term =(source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_y+pow(DD,SpecularPower)*SpecularCoeff);
    Blue_term =(source.get_light_intensity())*((shadow*DiffuseCoeff*D+AmbientCoeff)*colour_z+pow(DD,SpecularPower)*SpecularCoeff);
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
        cout<<"This should never happen \n";
    }
    vector3 RGB(Red_term, Green_term, Blue_term);
    return RGB;
}

float plane::ray_plane_intersection(vector3 ray_point, vector3 ray_direction){
    vector3 normal(normal_x, normal_y, normal_z);
    normal.normalize();
     if (ray_point.dotproduct(normal,ray_direction)!=0){

        return (( point_D- ray_point.dotproduct(normal,ray_point))/(ray_point.dotproduct(normal,ray_direction)));

    }
    else{
        return 0;
    }

}