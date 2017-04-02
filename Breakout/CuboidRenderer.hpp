#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif

#include "Renderer.hpp"

//Gameobject component that renders a cuboid

class CuboidRenderer : public Renderer{
	public:
		//Inherited render method, runs every frame
		void Render();
		//Empty constructor
		CuboidRenderer(GameObject& obj);
		//Constructors with size
		CuboidRenderer(const float width, const float height, const float length, GameObject& obj);
		CuboidRenderer(const float width, const float height, const float length, GameObject& obj, unsigned int spriteHandle);
	private:
		//Texture to render on cuboid faces
		int m_texture;
};
