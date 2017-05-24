# Ray Tracer

Course work for EngD VFX module. Aim: render skeleton fight scene from 1963 film 'Jason and the argonauts'.

![capture](https://cloud.githubusercontent.com/assets/25514442/26422519/20e50f90-40c2-11e7-9433-e1fa3674817d.PNG)

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
### Future Improvements:
* Soft shadows
* mesh class
* multi-threading
