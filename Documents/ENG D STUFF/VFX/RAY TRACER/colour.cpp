#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include"colour.hpp"
#include "vec3.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "search_tree.hpp"
#define infinity INT_MAX

 void TriangleColour::phong_areas(int*faces, int* face_normals, float*normals, float*vertices, float* areas, float *edges, int number_of_faces){
	for (int i=0; i<number_of_faces; i++){
		int c1 = faces[3*i] -1, c2 = faces[3*i+1]-1, c3 = faces[3*i+2] -1 ;
		int	n1 = face_normals[3*i]-1, n2 = face_normals[3*i+1]-1, n3= face_normals[3*i+2]-1;
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

 int TriangleColour::shadows(float* triangle_intersections, int*faces, float*vertices, vector3 point, vector3 l, const int* sphere_colour){
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

vector3 TriangleColour::phong_normal(int triangle, float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, vector3 point){
    float R,G,Bc, B,C, P_P1, P_P2, P_P3, semiPerimeter1, semiPerimeter2, semiPerimeter3, alpha1, alpha2, alpha3;
    int c_m1, c_m2, c_m3, n1, n2, n3;
    c_m1 = face[3*triangle] -1, c_m2 = face[3*triangle+1]-1, c_m3 = face[3*triangle+2] -1 ;
    n1 = face_normals[3*triangle]-1, n2 = face_normals[3*triangle+1]-1, n3= face_normals[3*triangle+2]-1;
    vector3 point1(vertices[3*c_m1], vertices[3*c_m1+1], vertices[3*c_m1+2]);
    vector3 point2(vertices[3*c_m2], vertices[3*c_m2+1], vertices[3*c_m2+2]);
    vector3 point3(vertices[3*c_m3], vertices[3*c_m3+1], vertices[3*c_m3+2]);
    vector3 N1(normals[3*n1], normals[3*n1+1], normals[3*n1+2]);
    vector3 N2(normals[3*n2], normals[3*n2+1], normals[3*n2+2]);
    vector3 N3(normals[3*n3], normals[3*n3+1], normals[3*n3+2]);

    P_P1 = sqrt(vector3::dotproduct(vector3::vec_add(point1, vector3::vec_scal_mult(-1, point)),vector3::vec_add(point1, vector3::vec_scal_mult(-1, point))));
    P_P2= sqrt(vector3::dotproduct(vector3::vec_add(point, vector3::vec_scal_mult(-1, point2)),vector3::vec_add(point, vector3::vec_scal_mult(-1, point2))));
    P_P3 = sqrt(vector3::dotproduct(vector3::vec_add(point, vector3::vec_scal_mult(-1, point3)),vector3::vec_add(point, vector3::vec_scal_mult(-1, point3))));

    semiPerimeter1 = (P_P3+edges[3*triangle+1]+P_P2)/2.0f;
    semiPerimeter2 = (P_P3+edges[3*triangle+2]+P_P1)/2.0f;
    semiPerimeter3 = (edges[3*triangle]+P_P2+P_P1)/2.0f;

    alpha1 = sqrt(semiPerimeter1*(semiPerimeter1 - edges[3*triangle+1])*(semiPerimeter1- P_P2)*(semiPerimeter1 -P_P3))/areas[triangle];
    alpha2 = sqrt(semiPerimeter2*(semiPerimeter2 - edges[3*triangle+2])*(semiPerimeter2- P_P1)*(semiPerimeter2 -P_P3))/areas[triangle];
    alpha3 = sqrt(semiPerimeter3*(semiPerimeter3 - edges[3*triangle])*(semiPerimeter3- P_P2)*(semiPerimeter3 -P_P1))/areas[triangle];

    vector3 N = vector3::vec_add3(vector3::vec_scal_mult(alpha1, N1), vector3::vec_scal_mult(alpha2, N2), vector3::vec_scal_mult(alpha3, N3));

    return N;
}
vector3 TriangleColour::intersection_colour(vector3 d, vector3 eye, search_tree* root,  float* vertices, float*normals, int*faces, int*face_normals, float* areas, float*edges, const int* tri_colour, Light sun, scene myscene){
    Bounding_box B_root(root->parameters[0],root->parameters[1], root->parameters[2],root->parameters[3],root->parameters[4],root->parameters[5]);
    int c1, c2,c3, c_m1, c_m2, c_m3;
    std::vector<float>  output;
    output.clear();
    if(B_root.ray_box_intersection(eye, d)==1){
        search_tree::traverse_tree(root, eye, d, &output);
    }
    float *k=new float[output.size()+1];
    k[0]=-1;
    if (output.size()>1){
        k[0]=output.size();
        for(int g=1; g<output.size()+1;g++){
            k[g] = output[g-1];
        }
    }
    if( (k[0]!=-1)&&(k[0]>0)){
        float* t_values = new float[k[0]];
        int min_value=-1, t_min = infinity, index;
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
            int m = k[min_value+1], n1, n2, n3,s;
            c_m1 = faces[3*m] -1, c_m2 = faces[3*m+1]-1, c_m3 = faces[3*m+2] -1 ;
            triangle tri(vertices[3*c_m1], vertices[3*c_m1+1], vertices[3*c_m1+2], vertices[3*c_m2], vertices[3*c_m2+1],vertices[3*c_m2+2], vertices[3*c_m3], vertices[3*c_m3+1], vertices[3*c_m3+2], tri_colour);
            t = tri.ray_triangle_intersection(eye,d);

            if(t!=0){
                tri.set_lighting_constants(0.5, 1*255, 0.3, 170);
                vector3 point = vector3::vec_add(eye, vector3::vec_scal_mult(t-0.001f,d));
                vector3 l = sun.get_light_direction(point);
                vector3 normal=tri.get_triangle_normal();  

                std::vector<float> output2;
                output2.clear();
                if(B_root.ray_box_intersection(point, l)==1){	
                    search_tree::traverse_tree(root, point, l, &output2);
                }
                float *k2=new float[output2.size()+1];
                k2[0]=-1;
                if (output2.size()>1){
                    k2[0]=output2.size();
                    for(int g=1; g<output2.size()+1;g++){
                        k2[g] = output2[g-1];
                    }
                }
                s = TriangleColour::shadows(k2, faces, vertices, point, l, tri_colour);		
                delete k2;
                vector3 phong_normal = TriangleColour::phong_normal(m, vertices, normals, faces, face_normals,  areas, edges, point);

                vector3 RGB = tri.determine_colour(point, l, d, sun, phong_normal, myscene,s);
                delete t_values;
                delete k;
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

void TriangleColour::anti_aliasing(float ratio, vector3 u, vector3 v, vector3 camera_origin, search_tree* root,  float* vertices, float*normals, int*face, int*face_normals, float* areas, float*edges, const int* tri_colour, Light sun, scene myscene, std::vector<vector3> *colours, vector3 L, int i, int j, int it){
    float I,J;
    for (int k=0; k<4; k++){
        I = i+1*k%2/(pow(2,(it+1))), J = j-1*(k>2)/(pow(2,(it+1)));
        vector3 s = vector3::vec_add3(L, vector3::vec_scal_mult(-1*(I)*ratio,u), vector3::vec_scal_mult(-1*(J)*ratio,v) );
        vector3 d(s.get_x()-camera_origin.get_x(),s.get_y()-camera_origin.get_y(),s.get_z()-camera_origin.get_z());
        d.normalize();
        vector3 RGB = TriangleColour::intersection_colour(d, camera_origin, root, vertices, normals, face, face_normals, areas, edges, tri_colour, sun, myscene);
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
        TriangleColour::anti_aliasing( ratio, u,  v,  camera_origin,  root,  vertices,normals,face, face_normals,  areas, edges,tri_colour,sun, myscene, colours, L,I,J, it);
    }
}