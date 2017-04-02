#include "GeometryCreator.hpp"
//Method for creating a display list for a cube
size_t makeCube(){
	//The vertices of the cube (length 1 centered on 0,0,0)
	static float vertices[8][3] = 
		{
			{-0.5f, -0.5f, -0.5f}, // front
			{0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, -0.5f, 0.5f}, // back 
			{0.5f, -0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f}
		};

	// indices for the cube
	static size_t faces[6][4] =
		{
			{0, 1, 2, 3},  // front
			{5, 4, 7, 6},  // back
			{4, 0, 3, 7},  // left
			{1, 5, 6, 2},  // right
			{4, 5, 1, 0},  // bottom
			{3, 2, 6, 7}   // top
		};

	// compile into a display list
	size_t handle = glGenLists(1);

	glNewList(handle, GL_COMPILE);
	glBegin(GL_QUADS);
	for (size_t f=0;f<6;f++) // for each face
	for (size_t v=0;v<4;v++) 
		glVertex3fv(vertices[faces[f][v]]);
	glEnd();
	glEndList();
	//Return the display list
	return handle;

}
//Method for creating a display list for a square
size_t makeSquare(){
	//The vertices of the square (length 1 centered on 0,0)
	float squareVertices[4][3]={
		{-0.5f,-0.5f,0},
		{0.5f,-0.5f,0},
		{0.5f,0.5f,0},
		{-0.5f,0.5f,0}
	};
	//Compule into a display list
	size_t handle = glGenLists(1);
	glNewList(handle,GL_COMPILE);
	glBegin(GL_QUADS);
	//Simple 0,1,2,3 indices
	for(size_t v=0;v<4;v++)
		glVertex3fv(squareVertices[v]);
	glEnd();
	glEndList();
	//Return the display list
	return handle;
}
