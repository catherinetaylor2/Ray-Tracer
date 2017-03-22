#include <iostream>
#include <cmath>
#include <vector>
#include"colour.hpp"
#include "vec3.hpp"

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