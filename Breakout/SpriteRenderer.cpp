#ifndef SPRITE_RENDERER
#define SPRITE_RENDEDER

#include "SpriteRenderer.hpp"
#include "GameObject.hpp"
#include "UIRenderer.hpp"
#include "Colours.hpp"
#include <cstdio>

//Rendering component for 2D objects

//Constructor, sets gameobject reference and a default size 1,1
SpriteRenderer::SpriteRenderer(GameObject &obj) : Renderer(obj){
	w = 1.0f;
	h = 1.0f;
	setColor(white);
}
//Constructor, sets gameobject reference and a size
SpriteRenderer::SpriteRenderer(const float width, const float height,GameObject& obj) : Renderer(obj){
	w=width;
	h=height;
	setColor(white);
}
//Constructor, sets gameobject reference, texture and size
SpriteRenderer::SpriteRenderer(const float width, const float height,GameObject& obj, unsigned int spriteHandle) : Renderer(obj){
	m_texture = spriteHandle;
	SpriteRenderer(width,height,obj);

}

//Renders the sprite
void SpriteRenderer::Render(){
	setRenderColor(m_color);
	//Render square if no texture
	if(m_texture==0){
		renderSquare(gameObject.x-w/2,gameObject.y-h/2,w,h,m_color);
	}else{
		//Render texture
		renderTexture(gameObject.x-w/2,gameObject.y-h/2,w,h,m_texture);
	}
}

#endif
