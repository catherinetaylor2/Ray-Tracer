#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include"readObj.hpp"


ObjFile::ObjFile(const char* name){
  /*File_Name = name;*/
	fn = name;
}

 float* ObjFile::get_vertices(void){
  char str[1000];
  float f1, f2, f3;
  std::string s = "a";
  FILE * myObject;
  int k_v = 0;
  int t;

  myObject = fopen(fn.c_str(), "r");

  while (s != "v"){
   t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }
  do{  
   t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;
    k_v=k_v+1;
  }while (s != "vt");

  int retval = fclose(myObject);
  myObject = fopen(fn.c_str(), "r");
  number_of_vertices = k_v;
  float* V = new float[3*number_of_vertices];

  while (s != "v"){
   t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }
  for(int i=0; i<3*number_of_vertices; i+=3){
    V[i] = f1;
    V[i+1] = f2;
    V[i+2]=f3; 
 t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
  }
  return V;
 }

float* ObjFile::get_normals(void){
  char str[1000];
  float f1, f2, f3;
  std::string s = "a";
  FILE * myObject;
  int k_vn=0, t;

  myObject = fopen(fn.c_str(), "r");


  while (s != "vn"){
   t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }

  do{  
    t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;
    k_vn=k_vn+1;
  }while (s == "vn");

  fclose(myObject);
  myObject = fopen(fn.c_str(), "r");

  number_of_normals = k_vn;
  float* N = new float[3*number_of_normals];

  while (s != "vn"){
  t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }

  for(int i=0; i<3*number_of_normals; i+=3){
    N[i] = f1;
    N[i+1] = f2;
    N[i+2]=f3;   
    fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
  }

return N;
}

int* ObjFile::get_faceV(void){
  char str[1000], c1, c2, c3, c4, c5, c6;
  float f1, f2, f3;
  int i1, i2, i3, i4, i5, i6, i7, i8, i9;
  std::string s = "a";
  FILE * myObject;
  int k_vf=0, t;

  myObject = fopen(fn.c_str(), "r");
 t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
  s = str; 
  while (s != "vn"){
    t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }
  for(int i=0; i< number_of_normals-1; i++){
   t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;
  }
  do{    
    s = str;
    k_vf=k_vf+1;
    t=fscanf(myObject, "%s %i %c %i %c %i %i %c %i %c %i %i %c %i %c %i", str, &i1, &c1, &i2, &c2, &i3, &i4, &c3, &i5, &c4, &i6, &i7, &c5, &i8, &c6, &i9);
  }while(t!=EOF);

 
  fclose(myObject);
  myObject = fopen(fn.c_str(), "r");
  fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
  s = str; 
  while (s != "vn"){
    t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }

  for(int i=0; i< number_of_normals-1; i++){
    t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;
  }

  number_of_faces = k_vf-1;
  int* FV = new int[3*number_of_faces];

  for(int i=0; i<3*number_of_faces; i+=3){
   t=fscanf(myObject, "%s %i %c %i %c %i %i %c %i %c %i %i %c %i %c %i", str, &i1, &c1, &i2, &c2, &i3, &i4, &c3, &i5, &c4, &i6, &i7, &c5, &i8, &c6, &i9);
    s=str;
    FV[i] = i1;
    FV[i+1]=i4;
    FV[i+2]=i7;
  }
  return FV;
}

int* ObjFile::get_faceN(void){
  char str[1000], c1, c2, c3, c4, c5, c6;
  float f1, f2, f3;
  int i1, i2, i3, i4, i5, i6, i7, i8, i9;
  std::string s = "a";
  FILE * myObject;
  int k_vf=0, t;

  myObject = fopen(fn.c_str(), "r");
  t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
  s = str; 
  while (s != "vn"){
   t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }
  for(int i=0; i< number_of_normals-1; i++){
    t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;
  }
  do{    
    s = str;
    k_vf=k_vf+1;
    t= fscanf(myObject, "%s %i %c %i %c %i %i %c %i %c %i %i %c %i %c %i", str, &i1, &c1, &i2, &c2, &i3, &i4, &c3, &i5, &c4, &i6, &i7, &c5, &i8, &c6, &i9);
  }while(t!=EOF);

 
  fclose(myObject);
  myObject = fopen(fn.c_str(), "r");
 t= fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
  s = str; 
  while (s != "vn"){
    fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;  
  }

  for(int i=0; i< number_of_normals-1; i++){
    t=fscanf(myObject, "%s %f %f %f" , str, &f1, &f2, &f3);
    s = str;
  }

number_of_faces = k_vf-1;
std::cout<<"face "<<number_of_faces<<"\n";
  int* FN = new int[3*number_of_faces];

  for(int i=0; i<3*number_of_faces; i+=3){
    t=fscanf(myObject, "%s %i %c %i %c %i %i %c %i %c %i %i %c %i %c %i", str, &i1, &c1, &i2, &c2, &i3, &i4, &c3, &i5, &c4, &i6, &i7, &c5, &i8, &c6, &i9);
    s=str;
    FN[i] = i3;
    FN[i+1]=i6;
    FN[i+2]=i9;
  }
  return FN;
}

int ObjFile::get_number_of_faces(void){
  return number_of_faces;
}

