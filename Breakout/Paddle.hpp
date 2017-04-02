#include "GameObject.hpp"

//A moveable paddle object, with attached collider
class Paddle : public GameObject{
	public:
		//Constructor
		Paddle(const int xpos, const int ypos, const int width, const int height, const float moveSpeed, const int xPlusLimit, const int xMinusLimit);
		//Deconstructor
		~Paddle();
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
		//Width height of paddle and speed it can move each frame
		float w,h,speed;
		//Limits to where the paddle can move in the x axis
		int xPlusBoundary;
		int xMinusBoundary;
};
