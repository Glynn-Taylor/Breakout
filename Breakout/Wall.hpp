#include "GameObject.hpp"

//A solid wall object that is immovable
class Wall : public GameObject{
	public:
		Wall(const int xpos, const int ypos, const int width, const int height);
		Wall(const int xpos, const int ypos, const int width, const int height, const float color[3]);
		~Wall();
		//Called when the gameobject is registered
		void onStart();
		//Called every frame by the containing scene
		void onRender();
		//Called every frame by the containing scene
		void onUpdate();
		//Called every frame by the containing scene with an orthographic camera setup
		void onUI();
		void onKeyDown(unsigned char key);
		void onKeyUp(unsigned char key);
		//Called when the ball collides with another collider
		void onCollide(Collider* other, CollisionInfo collideInfo);
	private:
		//Width and height of the wall
		float w,h;
		//colour of the wall in RGB
		float colour[3];
};
