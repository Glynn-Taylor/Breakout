#include "GameObject.hpp"

//A brick that the ball can bounce off of for points (destroys the brick)
class Brick : public GameObject{
	public:
		//Which row in the wall the brick is on, for colour and scoring
		int row;
		//Constructor
		Brick(const int xpos, const int ypos, const int width, const int height, const int brickrow);
		//Deconstructor
		~Brick();
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
		//Width and height of the brick
		float w,h;
		//colour of the brick in RGB
		float colour[3];
};
