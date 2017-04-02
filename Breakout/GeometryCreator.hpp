#ifndef GEOMETRY_CREATOR
#define GEOMETRY_CREATOR

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Method for creating a display list for a cube
size_t makeCube();
//Method for creating a display list for a square
size_t makeSquare();

#endif
