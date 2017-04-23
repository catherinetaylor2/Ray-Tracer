#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <algorithm>
#include"colour.hpp"
#include "vec3.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "search_tree.hpp"
#define infinity FLT_MAX

 void TriangleColour::phong_areas(int*faces, int* face_normals, float*normals, float*vertices, float* areas, float *edges, int number_of_faces){
	for (int i=0; i<number_of_faces; i++){
		int c1 = faces[3*i] -1, c2 = faces[3*i+1]-1, c3 = faces[3*i+2] -1, n1 = face_normals[3*i]-1, n2 = face_normals[3*i+1]-1, n3= face_normals[3*i+2]-1;
		float semiPerimeter;
		vector3 point1(vertices[3*c1], vertices[3*c1+1], vertices[3*c1+2]);
		vector3 point2(vertices[3*c2], vertices[3*c2+1], vertices[3*c2+2]);
		vector3 point3(vertices[3*c3], vertices[3*c3+1], vertices[3*c3+2]);
		vector3 N1(normals[3*n1], normals[3*n1+1], normals[3*n1+2]);
		vector3 N2(normals[3*n2], normals[3*n2+1], normals[3*n2+2]);
		vector3 N3(normals[3*n3], normals[3*n3+1], normals[3*n3+2]);
		edges[3*i] = sqrt(vector3::dotproduct(vector3::vec_add(point1, vector3::vec_scal_mult(-1, point2)),vector3::vec_add(point1, vector3::vec_scal_mult(-1, point2))));
		edges[3*i+1] = sqrt(vector3::dotproduct(vector3::vec_add(point3, vector3::vec_scal_mult(-1, point2)),vector3::vec_add(point3, vector3::vec_scal_mult(-1, point2))));
		edges[3*i+2] = sqrt(vector3::dotproduct(vector3::vec_add(point1, vector3::vec_scal_mult(-1, point3)),vector3::vec_add(point1, vector3::vec_scal_mult(-1, point3))));
    	semiPerimeter = (edges[3*i]+edges[3*i+1]+edges[3*i+2])/2.0f;
		areas[i] = sqrt(semiPerimeter*(semiPerimeter - edges[3*i])*(semiPerimeter- edges[3*i+1])*(semiPerimeter -edges[3*i+2]));
	}
 }

 int TriangleColour::shadows(int* triangle_intersections, int*faces, float*vertices, vector3 point, vector3 l, const int* sphere_colour){
    int s=1, index, c1, c2, c3;
    if( (triangle_intersections[0]!=-1)&&(triangle_intersections[0]>0)){
        for (int z=1; z<triangle_intersections[0]+1; z++){
            index = triangle_intersections[z];
            c1 = faces[3*index] -1, c2 = faces[3*index+1]-1, c3 = faces[3*index+2] -1 ;
            triangle tri2(vertices[3*c1], vertices[3*c1+1], vertices[3*c1+2], vertices[3*c2], vertices[3*c2+1],vertices[3*c2+2], vertices[3*c3], vertices[3*c3+1], vertices[3*c3+2], sphere_colour);
            float ss = tri2.ray_triangle_intersection( point, l);
            if ((ss)> 0){
                s = 0;
            }
        }
    }
    return s;
 }

vector3 TriangleColour::phong_normal(int triangle, float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, vector3 point, vector3 d, float **barycentric){
    float denominator;
    int c_m1, c_m2, c_m3, n1, n2, n3;
    c_m1 = face[3*triangle] -1, c_m2 = face[3*triangle+1]-1, c_m3 = face[3*triangle+2] -1 ;
    n1 = face_normals[3*triangle]-1, n2 = face_normals[3*triangle+1]-1, n3= face_normals[3*triangle+2]-1;
    vector3 point1(vertices[3*c_m1], vertices[3*c_m1+1], vertices[3*c_m1+2]);
    vector3 point2(vertices[3*c_m2], vertices[3*c_m2+1], vertices[3*c_m2+2]);
    vector3 point3(vertices[3*c_m3], vertices[3*c_m3+1], vertices[3*c_m3+2]);
    vector3 N1(normals[3*n1], normals[3*n1+1], normals[3*n1+2]);
    vector3 N2(normals[3*n2], normals[3*n2+1], normals[3*n2+2]);
    vector3 N3(normals[3*n3], normals[3*n3+1], normals[3*n3+2]);
    vector3 T = vector3::vec_add(point, vector3::vec_scal_mult(-1, point1));
    vector3 E1 = vector3::vec_add(point2, vector3::vec_scal_mult(-1, point1));
    vector3 E2 = vector3::vec_add(point3, vector3::vec_scal_mult(-1, point1));
    denominator = vector3::dotproduct( vector3::crossproduct(d, E2), E1);
    vector3 M (vector3::dotproduct(vector3::crossproduct(T, E1), E2),vector3::dotproduct(vector3::crossproduct(d, E2), T),vector3::dotproduct( vector3::crossproduct(T, E1), d));
    vector3 tuv = vector3::vec_scal_mult(1.0f/(float)denominator, M);
    vector3 N = vector3::vec_add3(vector3::vec_scal_mult(std::max((float)(1-(tuv.get_y()+tuv.get_z())),0.0f),N1),vector3::vec_scal_mult(std::max(tuv.get_y(), 0.0f),N2),vector3::vec_scal_mult(std::max(tuv.get_z(),0.0f),N3));
    (*barycentric)[0] =1.0f-(tuv.get_y()+tuv.get_z());
    (*barycentric)[1] =tuv.get_y();
    (*barycentric)[2] = tuv.get_z();
    return N;
}
float TriangleColour::find_intersection_point(search_tree* root, float*vertices, int* faces, vector3 eye, vector3 d, int* min_value, const int* tri_colour, int**k){
    Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
    std::vector<int>  output;
    float t_min = infinity;
	int c1, c2, c3;
    output.clear();
    if(B_root.ray_box_intersection(eye, d)==1){
        search_tree::traverse_tree(root, eye, d, &output);
    }
    *k=new int[output.size()+1];
    (*k)[0]=-1;
    if (output.size()>1){
        (*k)[0]=output.size();
        for(int g=1; g<(*k)[0]+1;g++){
            (*k)[g] = output[g-1];
        }
    }
    if( ((*k)[0]!=-1)&&((*k)[0]>0)){
        float* t_values = new float[(*k)[0]], t;
        int index;
        for (int z=1; z<(*k)[0]+1; z++){
            index = (*k)[z];
            c1 = faces[3*index] -1, c2 = faces[3*index+1]-1, c3 = faces[3*index+2] -1 ;
            triangle tri(vertices[3*c1], vertices[3*c1+1], vertices[3*c1+2], vertices[3*c2], vertices[3*c2+1], vertices[3*c2+2], vertices[3*c3], vertices[3*c3+1], vertices[3*c3+2], tri_colour);
            t = tri.ray_triangle_intersection(eye,d);
            t_values[z-1]=t;
        }
        for (int z=0; z<(*k)[0]; z++){
            if ((t_values[z]>0)){
                vector3 xyz = vector3::vec_add( eye , vector3::vec_scal_mult(t_values[z],d));
                if (xyz.get_z()<t_min){
                    t_min = xyz.get_z();
                    *min_value = z;
                }
            }
        }
        delete t_values;
    }
    return t_min;
}



vector3 TriangleColour::intersection_colour(vector3 d, vector3 eye, std::vector<search_tree*> root_data, std::vector<float*> mesh_data,std::vector<int*> mesh_data_i,  const int* tri_colour, Light sun, scene myscene, std::vector<unsigned char*> data_bmp, int* texture_data){
    int min_value1 = -1, min_value2 = -1, min_value, obj, min_value3 = -1, * k, *k2, *ks ;
    float t1 = TriangleColour::find_intersection_point(root_data[1], mesh_data[5], mesh_data_i[3], eye, d, &min_value1, tri_colour, &k), t;
    float t2 = TriangleColour::find_intersection_point(root_data[2], mesh_data[10], mesh_data_i[6], eye, d, &min_value2, tri_colour, &k2);
    float ts = TriangleColour::find_intersection_point(root_data[3], mesh_data[15], mesh_data_i[9], eye, d, &min_value3, tri_colour, &ks);

    if ((t2 < t1 )&&(t2<ts)){
        t=t2;
        min_value = min_value2;
        obj = 2;
        k = k2;
    }
    else if((t1<t2)&&(t1<=ts)){
        t=t1;
        min_value = min_value1;
        obj =1;
    }
    else{
        t=ts;
        min_value = min_value3;
        obj = 3;
        k=ks;
    }
    int ref=0, c_m1, c_m2, c_m3, *faces = mesh_data_i[0+obj*3], *face_normals = mesh_data_i[1+obj*3], *F_VT = mesh_data_i[2+obj*3],  texture_width = texture_data[0+obj*2], texture_height = texture_data[1+obj*2];
    float*vertices = mesh_data[0+obj*5], *normals = mesh_data[1+obj*5], *VT = mesh_data[2+obj*5], *areas = mesh_data[3+obj*5], *edges = mesh_data[4+obj*5];
    Bounding_box B_root(root_data[obj]->parameters[0],root_data[obj]->parameters[1], root_data[obj]->parameters[2],root_data[obj]->parameters[3],root_data[obj]->parameters[4],root_data[obj]->parameters[5]);
    unsigned char* data = data_bmp[obj];

    if (t < infinity){
        if (min_value == -1){
            vector3 RGB (0,0,0);
            delete k;
            if ((t2 < t1 )&&(t2<ts)){
                delete ks;
            }
            else if((t1<t2)&&(t1<=ts)){
                delete k2;
                delete ks;
            }
            else{
                delete k2;
            }
            return RGB;
        }
        else{
            int m = k[min_value+1], s, vt1, vt2, vt3;
            c_m1 = faces[3*m] -1, c_m2 = faces[3*m+1]-1, c_m3 = faces[3*m+2] -1 ;
            vt1 = F_VT[3*m]-1, vt2 = F_VT[3*m+1]-1, vt3 = F_VT[3*m+2]-1;
            float vt_1x = VT[2*vt1], vt_1y = VT[2*vt1+1], vt_2x = VT[2*vt2], vt_2y = VT[2*vt2+1], vt_3x = VT[2*vt3], vt_3y = VT[2*vt3+1], R,G,B;
            triangle tri(vertices[3*c_m1], vertices[3*c_m1+1], vertices[3*c_m1+2], vertices[3*c_m2], vertices[3*c_m2+1],vertices[3*c_m2+2], vertices[3*c_m3], vertices[3*c_m3+1], vertices[3*c_m3+2], tri_colour);
            t = tri.ray_triangle_intersection(eye,d);
            if((t!=0)){
                tri.set_lighting_constants((float)0.5, (float)1*255, (float)0.3, (float)170);
                vector3 point = vector3::vec_add(eye, vector3::vec_scal_mult(t-0.0035f,d));
                vector3 l = sun.get_light_direction(point);
                vector3 normal=tri.get_triangle_normal();

                std::vector<int> output2;
                output2.clear();
                if(B_root.ray_box_intersection(point, l)==1){
                    search_tree::traverse_tree(root_data[obj], point, l, &output2);
                }
                int *k3=new int[output2.size()+1];
                k3[0]=-1;
                if (output2.size()>1){
                    k3[0]=output2.size();
                    for(int g=1; g<k3[0]+1;g++){
                        k3[g] = output2[g-1];
                    }
                }
                s = TriangleColour::shadows(k3, faces, vertices, point, l, tri_colour);
                delete k3;
                float* barycentric = new float[3];
                vector3 phong_normal = TriangleColour::phong_normal(m, vertices, normals, faces, face_normals, areas, edges, eye, d, &barycentric);
                float r_g_b[3] = {0,0,0};

                if(obj==1){ //reflective sword code.
                   int*k4;
                    min_value = -1;
                    vector3 R = vector3::vec_scal_mult(2.0f*vector3::dotproduct(d, normal), normal);
                    vector3 H = vector3::vec_add(d, vector3::vec_scal_mult(-1,R));
                    H.normalize();
                    float t3 = TriangleColour::find_intersection_point(root_data[0], mesh_data[0], mesh_data_i[0], point, H, &min_value, tri_colour, &k4);
                    if (t3<infinity){
                        m = k4[min_value+1];
                        obj = 0;
                        int *faces1 = mesh_data_i[0+obj*3], *face_normals1 = mesh_data_i[1+obj*3], *F_VT1 = mesh_data_i[2+obj*3];
                        float *vertices1 = mesh_data[0+obj*5], *normals1 = mesh_data[1+obj*5], *VT1 = mesh_data[2+obj*5], *areas1 = mesh_data[3+obj*5], *edges1 = mesh_data[4+obj*5];
                        unsigned char *data1 = data_bmp[obj];
                     
                        c_m1 = faces1[3*m] -1, c_m2 = faces1[3*m+1]-1, c_m3 = faces1[3*m+2] -1 ;
                        triangle tri1(vertices1[3*c_m1], vertices1[3*c_m1+1], vertices1[3*c_m1+2], vertices1[3*c_m2], vertices1[3*c_m2+1],vertices1[3*c_m2+2], vertices1[3*c_m3], vertices1[3*c_m3+1], vertices1[3*c_m3+2], tri_colour);
                        tri1.set_lighting_constants((float)0.5, (float)1*255, (float)0.3, (float)170);
                        float *b2 = new float[3];
                        vector3 phong_normal1 = TriangleColour::phong_normal(m, vertices1, normals1, faces1, face_normals1, areas1, edges1, point, H, &b2);
                        delete b2;

                        int texture_width1 = texture_data[0+obj*2], texture_height1 = texture_data[1+obj*2];
                        vector3 point1 = vector3::vec_add(point, vector3::vec_scal_mult(t3,H));
                        vector3 l1 = sun.get_light_direction(point1);

                        float u_coord, v_coord, alpha, beta, v12r, v12g, v12b, v34r, v34g, v34b;
                        int v1x,v1y, v2x, v4y;
                        u_coord = (barycentric[0]*vt_1x +barycentric[1]*vt_2x+barycentric[2]*vt_3x)*texture_width1;
                        v_coord = (barycentric[0]*vt_1y +barycentric[1]*vt_2y+barycentric[2]*vt_3y)*texture_height1;
                        v1x = (int)floor(u_coord);
                        v1y = (int)ceil(v_coord);
                        v2x = (int)ceil(u_coord);
                        v4y = (int)floor(v_coord);
                        if (v1x<0){
                            v1x=0;
                        }
                        if (v2x<0){
                            v2x=0;
                        }
                        if (v1y<0){
                            v1y=0;
                        }
                        if (v4y<0){
                            v4y=0;
                        }

                        alpha = (float)(u_coord - (v2x - v1x)*v1x)/(float) (v2x - v1x);
                        beta = (float)(v_coord - (v1y - v4y)*v4y)/(float) (v1y - v4y);

                        if (alpha >1){
                            alpha=1;
                        }
                        if(beta>1){
                            beta =1;
                        }
                        v12r = (1-alpha)*data1[v1y*texture_width1*3 + 3*v1x] +  alpha*data1[v1y*texture_width1*3 + 3*v2x];
                        v12g = (1-alpha)*data1[v1y*texture_width1*3 + 3*v1x+1] +  alpha*data1[v1y*texture_width1*3 + 3*v2x+1];
                        v12b = (1-alpha)*data1[v1y*texture_width1*3 + 3*v1x+2] +  alpha*data1[v1y*texture_width1*3 + 3*v2x+2];

                        v34r =  (1-alpha)*data1[v4y*texture_width1*3 + 3*v1x] +  alpha*data1[v4y*texture_width1*3 + 3*v2x];
                        v34g =  (1-alpha)*data1[v4y*texture_width1*3 + 3*v1x+1] +  alpha*data1[v4y*texture_width1*3 + 3*v2x+1];
                        v34b =  (1-alpha)*data1[v4y*texture_width1*3 + 3*v1x+2] +  alpha*data1[v4y*texture_width1*3 + 3*v2x+2];
                        float colour1[] =  {(1-beta)*v12r + beta*v34r, (1-beta)*v12g + beta*v34g, (1-beta)*v12b + beta*v34b} ;
              
                        vector3 RGB_1 = tri1.determine_colour(point1, l1, d, sun, phong_normal1, myscene,s, colour1);
                        r_g_b [0] = RGB_1.get_x();
                        r_g_b[1] = RGB_1.get_y();
                        r_g_b[2]=RGB_1.get_z();
                    }                  
                   delete k4;                   
                 }
                 vector3 RGB1( r_g_b [0],  r_g_b [1],  r_g_b [2]);

           //bilinear interpolation
                float u_coord, v_coord, alpha, beta, v12r, v12g, v12b, v34r, v34g, v34b;
                int v1x,v1y, v2x, v4y;
                u_coord = (barycentric[0]*vt_1x +barycentric[1]*vt_2x+barycentric[2]*vt_3x)*texture_width;
                v_coord = (barycentric[0]*vt_1y +barycentric[1]*vt_2y+barycentric[2]*vt_3y)*texture_height;
				v1x = (int)floor(u_coord);
                v1y = (int)ceil(v_coord);
                v2x = (int)ceil(u_coord);
                v4y = (int)floor(v_coord);
                if (v1x<0){
                    v1x=0;
                }
                if (v2x<0){
                    v2x=0;
                }
                if (v1y<0){
                    v1y=0;
                }
                if (v4y<0){
                    v4y=0;
                }

                alpha = (float)(u_coord - (v2x - v1x)*v1x)/(float) (v2x - v1x);
                beta = (float)(v_coord - (v1y - v4y)*v4y)/(float) (v1y - v4y);

                if (alpha >1){
                    alpha=1;
                }
                if(beta>1){
                    beta =1;
                }
                v12r = (1-alpha)*data[v1y*texture_width*3 + 3*v1x] +  alpha*data[v1y*texture_width*3 + 3*v2x];
                v12g = (1-alpha)*data[v1y*texture_width*3 + 3*v1x+1] +  alpha*data[v1y*texture_width*3 + 3*v2x+1];
                v12b = (1-alpha)*data[v1y*texture_width*3 + 3*v1x+2] +  alpha*data[v1y*texture_width*3 + 3*v2x+2];

                v34r =  (1-alpha)*data[v4y*texture_width*3 + 3*v1x] +  alpha*data[v4y*texture_width*3 + 3*v2x];
                v34g =  (1-alpha)*data[v4y*texture_width*3 + 3*v1x+1] +  alpha*data[v4y*texture_width*3 + 3*v2x+1];
                v34b =  (1-alpha)*data[v4y*texture_width*3 + 3*v1x+2] +  alpha*data[v4y*texture_width*3 + 3*v2x+2];
                float colour[] =  {(1-beta)*v12r + beta*v34r, (1-beta)*v12g + beta*v34g, (1-beta)*v12b + beta*v34b} ;

                vector3 RGB2 = vector3::vec_add(tri.determine_colour(point, l, d, sun, phong_normal, myscene,s, colour), vector3::vec_scal_mult(1,RGB1));
                if (RGB2.get_x()>255){
                    R = 255;
                }
                else{
                    R = RGB2.get_x();
                }
                    if (RGB2.get_y()>255){
                     G = 255;
                }
                else{
                     G = RGB2.get_y();
                }
                    if (RGB2.get_z()>255){
                    B= 255;
                }
                else{
                    B = RGB2.get_z();
                }
                vector3 RGB(R,G,B);
                delete k;
                if ((t2 < t1 )&&(t2<ts)){
                    delete ks;
                }
                else if((t1<t2)&&(t1<=ts)){
                    delete k2;
                    delete ks;
                }
                else{
                    delete k2;
                }
                delete barycentric;
                return RGB;
            }
        }
    }
    else{
        vector3 RGB(0,0,0);
        delete k;
        if ((t2 < t1 )&&(t2<ts)){
            delete ks;
        }
        else if((t1<t2)&&(t1<=ts)){
            delete k2;
            delete ks;
        }
        else{
            delete k2;
        }
        return RGB;
    }
	vector3 RGB(0, 0, 0);
    delete k;
    delete k2;
    delete ks;
	return RGB;
}

void TriangleColour::anti_aliasing(std::vector<vector3> scene_pos, std::vector<search_tree*> root_data,  std::vector<float*> mesh_data, std::vector<int*> mesh_data_i, const int* tri_colour, Light sun, scene myscene, std::vector<vector3> *colours, vector3 L, float* ijit, std::vector<unsigned char*> data_bmp, int* texture_data){
    float I,J, i = ijit[0], j = ijit[1], it= ijit[2], ratio = ijit[3];
    vector3 u = scene_pos[0], v = scene_pos[1], camera_origin = scene_pos[2];
    search_tree* root = root_data[0];
    for (int k=0; k<4; k++){
        I = (float)(i+1*k%2/(pow(2,(it+1)))), J = (float)(j-1*(k>2)/(pow(2,(it+1))));
        vector3 s = vector3::vec_add3(L, vector3::vec_scal_mult(-1*(I)*ratio,u), vector3::vec_scal_mult(-1*(J)*ratio,v) );
        vector3 d(s.get_x()-camera_origin.get_x(),s.get_y()-camera_origin.get_y(),s.get_z()-camera_origin.get_z());
        d.normalize();
        vector3 RGB = TriangleColour::intersection_colour(d, camera_origin, root_data, mesh_data, mesh_data_i, tri_colour, sun, myscene, data_bmp, texture_data);
        (*colours).push_back(RGB);
    }
    int quadrant = -1;
    float sum = ((*colours)[it].get_x()+ (*colours)[it+1].get_x()+ (*colours)[it+2].get_x()+(*colours)[it+3].get_x()/4.0f);
    if(sum>0){
        if(((*colours)[0].get_x()==0)&&((*colours)[1].get_x()!=0)&&((*colours)[2].get_x()!=0)&&((*colours)[3].get_x()!=0)){
            quadrant = 0;
        }
        else if (((*colours)[0].get_x()!=0)&&((*colours)[1].get_x()==0)&&((*colours)[2].get_x()!=0)&&((*colours)[3].get_x()!=0)){
            quadrant = 1;
        }
        else  if(((*colours)[0].get_x()!=0)&&((*colours)[1].get_x()!=0)&&((*colours)[2].get_x()==0)&&((*colours)[3].get_x()!=0)){
            quadrant = 2;
        }
        else if(((*colours)[0].get_x()!=0)&&((*colours)[1].get_x()!=0)&&((*colours)[2].get_x()!=0)&&((*colours)[3].get_x()==0)){
            quadrant = 3;
        }
        else{
            for(int k=0; k<4;k++){
                if((*colours)[k].get_x()/sum >0.75){
                    quadrant = k;
                }
            }
        }
    }
    if ((quadrant==-1)||(it>8)){
        return;
    }
    else{
        if(quadrant == 0){
            I = (float)(i+1*quadrant%2/(pow(2,(it+1))));
            J = (float)(j-1*(quadrant>2)/(pow(2,(it+1))));
        }
        if(quadrant ==1){
            I = (float)(i+1*quadrant%2/(pow(2,(it+1)))-1/(pow(2,(it+2))));
            J = (float)(j-1*(quadrant>2)/(pow(2,(it+1))));
        }
        if(quadrant==2){
            I = (float)(i+1*quadrant%2/(pow(2,(it+1))));
            J = (float)(j-1*(quadrant>2)/(pow(2,(it+1)))+1/(pow(2,(it+2))));
        }
        if(quadrant==3){
            I = (float)(i+1*quadrant%2/(pow(2,(it+1)))-1/(pow(2,(it+2))));
            J = (float)(j-1*(quadrant>2)/(pow(2,(it+1)))+1/(pow(2,(it+2))));
        }
        it=it+1;
        ijit[0] = I;
        ijit[1] = J;
        ijit[2]=it;
        ijit[3] = ratio;
        TriangleColour::anti_aliasing(scene_pos,  root_data,  mesh_data,mesh_data_i,tri_colour,sun, myscene, colours, L,ijit, data_bmp, texture_data);
    }
}