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
    float P_P1, P_P2, P_P3, semiPerimeter1, semiPerimeter2, semiPerimeter3, alpha1, alpha2, alpha3, denominator;
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
vector3 TriangleColour::intersection_colour(vector3 d, vector3 eye, search_tree* root,  float* vertices, float*normals, int*faces, int*face_normals, int* F_VT, float *VT, float* areas, float*edges, const int* tri_colour, Light sun, scene myscene, unsigned char* data, int texture_width, int texture_height){
    Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
    int c1, c2,c3, c_m1, c_m2, c_m3;
    std::vector<int>  output;
    output.clear();
    if(B_root.ray_box_intersection(eye, d)==1){
        search_tree::traverse_tree(root, eye, d, &output);
    }
    int *k=new int[output.size()+1];
    k[0]=-1;
    if (output.size()>1){
        k[0]=output.size();
        for(int g=1; g<k[0]+1;g++){
            k[g] = output[g-1];
        }
    }
    if( (k[0]!=-1)&&(k[0]>0)){
        float* t_values = new float[k[0]];
        float t_min = infinity;
        int min_value=-1, index;
        float t;
        for (int z=1; z<k[0]+1; z++){
            index = k[z];
            c1 = faces[3*index] -1, c2 = faces[3*index+1]-1, c3 = faces[3*index+2] -1 ;
            triangle tri(vertices[3*c1], vertices[3*c1+1], vertices[3*c1+2], vertices[3*c2], vertices[3*c2+1], vertices[3*c2+2], vertices[3*c3], vertices[3*c3+1], vertices[3*c3+2], tri_colour);
            t = tri.ray_triangle_intersection(eye,d);
            t_values[z-1]=t;
        }
        for (int z=0; z<k[0]; z++){
            if ((t_values[z]>0)){
                vector3 xyz = vector3::vec_add( eye , vector3::vec_scal_mult(t_values[z],d));
                if (xyz.get_z()<t_min){
                    t_min = xyz.get_z();
                    min_value = z;					
                }
            }
        }
        if (min_value == -1){
            vector3 RGB (0,0,0);
            delete k;
            delete t_values;
            return RGB;
        }
        else{
            int m = k[min_value+1], s, vt1, vt2, vt3;
            c_m1 = faces[3*m] -1, c_m2 = faces[3*m+1]-1, c_m3 = faces[3*m+2] -1 ;
            vt1 = F_VT[3*m]-1, vt2 = F_VT[3*m+1]-1, vt3 = F_VT[3*m+2]-1;
            float vt_1x = VT[2*vt1], vt_1y = VT[2*vt1+1], vt_2x = VT[2*vt2], vt_2y = VT[2*vt2+1], vt_3x = VT[2*vt3], vt_3y = VT[2*vt3+1];
            triangle tri(vertices[3*c_m1], vertices[3*c_m1+1], vertices[3*c_m1+2], vertices[3*c_m2], vertices[3*c_m2+1],vertices[3*c_m2+2], vertices[3*c_m3], vertices[3*c_m3+1], vertices[3*c_m3+2], tri_colour);
            t = tri.ray_triangle_intersection(eye,d);

            if(t!=0){
                tri.set_lighting_constants(0.5, 1*255, 0.3, 170);
                vector3 point = vector3::vec_add(eye, vector3::vec_scal_mult(t-0.0035f,d));
                vector3 l = sun.get_light_direction(point);
                vector3 normal=tri.get_triangle_normal();  

                std::vector<int> output2;
                output2.clear();
                if(B_root.ray_box_intersection(point, l)==1){	
                    search_tree::traverse_tree(root, point, l, &output2);
                }
                int *k2=new int[output2.size()+1];
                k2[0]=-1;
                if (output2.size()>1){
                    k2[0]=output2.size();
                    for(int g=1; g<k2[0]+1;g++){
                        k2[g] = output2[g-1];
                    }
                }
                s = TriangleColour::shadows(k2, faces, vertices, point, l, tri_colour);		
                delete k2;
                float* barycentric = new float[3];
                vector3 phong_normal = TriangleColour::phong_normal(m, vertices, normals, faces, face_normals, areas, edges, eye, d, &barycentric);

           //bilinear interpolation 
                float u_coord, v_coord, alpha, beta, v12r, v12g, v12b, v34r, v34g, v34b;
                int v1x,v1y, v2x, v4y;
                u_coord = (barycentric[0]*vt_1x +barycentric[1]*vt_2x+barycentric[2]*vt_3x)*texture_width;
                v_coord = (barycentric[0]*vt_1y +barycentric[1]*vt_2y+barycentric[2]*vt_3y)*texture_height;
                v1x = floor(u_coord);
                v1y = ceil(v_coord);
                v2x = ceil(u_coord);
                v4y = floor(v_coord);   
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
            
                vector3 RGB = tri.determine_colour(point, l, d, sun, phong_normal, myscene,s, colour);
                delete t_values;
                delete k;
                delete barycentric;
                return RGB;
            }	
        }
    }
    else{
        vector3 RGB(0,0,0);	
        delete k;
        return RGB;
    }
}

void TriangleColour::anti_aliasing(std::vector<vector3> scene_pos, search_tree* root,  std::vector<float*> mesh_data, std::vector<int*> mesh_data_i, const int* tri_colour, Light sun, scene myscene, std::vector<vector3> *colours, vector3 L, float* ijit,unsigned char* data, int* texture_data){
    float I,J, i = ijit[0], j = ijit[1], it= ijit[2], ratio = ijit[3], *vertices = mesh_data[0], *normals = mesh_data[1], *textures = mesh_data[2], *areas = mesh_data[3], *edges = mesh_data[4];
    int texture_width = texture_data[0], texture_height = texture_data[1],*face = mesh_data_i[0], *face_normals = mesh_data_i[1], *face_texture = mesh_data_i[2];
    vector3 u = scene_pos[0], v = scene_pos[1], camera_origin = scene_pos[2];

    for (int k=0; k<4; k++){
        I = i+1*k%2/(pow(2,(it+1))), J = j-1*(k>2)/(pow(2,(it+1)));
        vector3 s = vector3::vec_add3(L, vector3::vec_scal_mult(-1*(I)*ratio,u), vector3::vec_scal_mult(-1*(J)*ratio,v) );
        vector3 d(s.get_x()-camera_origin.get_x(),s.get_y()-camera_origin.get_y(),s.get_z()-camera_origin.get_z());
        d.normalize();
        vector3 RGB = TriangleColour::intersection_colour(d, camera_origin, root, vertices, normals, face, face_normals, face_texture, textures, areas, edges, tri_colour, sun, myscene, data, texture_width,texture_height);
        (*colours).push_back(RGB);
    }
    int quadrant = -1;
    float sum = (*colours)[it].get_x()+(*colours)[it+1].get_x()+(*colours)[it+2].get_x()+(*colours)[it+3].get_x()/4.0f;
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
            I = i+1*quadrant%2/(pow(2,(it+1)));
            J =  j-1*(quadrant>2)/(pow(2,(it+1)));
        }
        if(quadrant ==1){
            I = i+1*quadrant%2/(pow(2,(it+1)))-1/(pow(2,(it+2)));
            J =  j-1*(quadrant>2)/(pow(2,(it+1)));
        }
        if(quadrant==2){
            I = i+1*quadrant%2/(pow(2,(it+1)));
            J =  j-1*(quadrant>2)/(pow(2,(it+1)))+1/(pow(2,(it+2)));
        }
        if(quadrant==3){
            I = i+1*quadrant%2/(pow(2,(it+1)))-1/(pow(2,(it+2)));
            J =  j-1*(quadrant>2)/(pow(2,(it+1)))+1/(pow(2,(it+2)));
        }
        it=it+1;
        ijit[0] = I;
        ijit[1] = J;
        ijit[2]=it;
        ijit[3] = ratio;
        TriangleColour::anti_aliasing(scene_pos,  root,  mesh_data,mesh_data_i,tri_colour,sun, myscene, colours, L,ijit, data, texture_data);
    }
}