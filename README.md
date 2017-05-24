# Ray Tracer

Course work for EngD VFX module. Aim: render skeleton fight scene from 1963 film 'Jason and the argonauts'.

![textured](https://cloud.githubusercontent.com/assets/25514442/25014785/1a3a2d36-2071-11e7-9c47-9bbecb2e3909.PNG)

### Input
The objects in the scene and the textures must be have the following format:
* Triangular meshes:  obj files.
* Texture images: bitmap

### Method
This raytracing model contains:
* phong shading
* reflections
* hard shadows
* anti aliasing using adaptive sampling
* texture maps
* bounding boxes using BSTs

### How to Compile

CL:
     cl /O2 /MP ray_tracer.cpp light.cpp scene.cpp Triangle.cpp vec3.cpp search_tree.cpp colour.cpp read_obj.cpp  BITMAP.cpp /openmp /EHsc 

