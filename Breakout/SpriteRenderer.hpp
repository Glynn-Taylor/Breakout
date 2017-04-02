#include "Renderer.hpp"

//Rendering component for 2D objects
class SpriteRenderer : public Renderer{
	public:
		//Renders the sprite
		void Render();
		//Constructor, sets gameobject reference and a default size 1,1
		SpriteRenderer(GameObject& obj);
		//Constructor, sets gameobject reference and size
		SpriteRenderer(const float width, const float height, GameObject& obj);
		//Constructor, sets gameobject reference, texture and size
		SpriteRenderer(const float width, const float height, GameObject& obj, unsigned int spriteHandle);
	private:
		//Handle for texture
		int m_texture;
};
