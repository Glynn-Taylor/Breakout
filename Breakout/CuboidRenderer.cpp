#ifndef CUBOID_RENDERER
#define CUBOID_RENDERER

#include "CuboidRenderer.hpp"
#include "GameObject.hpp"
#include "UIRenderer.hpp"
#include "Colours.hpp"
#include "GeometryCreator.hpp"
#include <cstdio>
#include "Display.hpp"

//Gameobject component that renders a cuboid

//Default constructor, default size of 1,1,1
CuboidRenderer::CuboidRenderer(GameObject &obj) : Renderer(obj){
	w = 1.0f;
	h = 1.0f;
	l = 1.0f;
	setColor(white);
}
//Constructor with custom size
CuboidRenderer::CuboidRenderer(const float width, const float height, const float length, GameObject& obj) : Renderer(obj){
	w=width;
	h=height;
	l=length;
	setColor(white);
}
//Constructor with custom size and texture
CuboidRenderer::CuboidRenderer(const float width, const float height, const float length, GameObject& obj, unsigned int spriteHandle) : Renderer(obj){
	m_texture = spriteHandle;
	CuboidRenderer(width,height,length,obj);
}


//Inherited render method, runs every frame
void CuboidRenderer::Render(){
	//Create a copy of model view matrix on top of stack
	glPushMatrix();
		//Translate to origin of gameobject
		glTranslatef(gameObject.x,gameObject.y,l/2);
		setRenderColor(m_color);
		//Translate size
		glScalef(w,h,l);
		// Call the display list
		if(m_texture==0){
			glCallList(CubeMesh);
		}else{
			glCallList(CubeMesh);
			//Render texture
		}
	//Remove copy of model view matrix
	glPopMatrix();
}

#endif
