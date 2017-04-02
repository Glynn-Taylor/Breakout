#include "GameObject.hpp"

//Moving ball gameobject, can collide with other gameobjects and has a velocity (rigidbody)

class Ball : public GameObject{
	public:
		//size of the ball (x & y & z)
		int size;
		//Constructor
		Ball(const int xpos, const int ypos, const int width);
		//Deconstructor
		~Ball();
		//Called when the gameobject is registered
		void onStart();
		//Called every frame by the containing scene
		void onRender();
		//Called every frame by the containing scene
		void onUpdate();
		//Called every frame by the containing scene with an orthographic camera setup
		void onUI();
		//Keyboard input handlers
		void onKeyDown(unsigned char key);
		void onKeyUp(unsigned char key);
		//Called when the ball collides with another collider
		void onCollide(Collider* other,CollisionInfo collideInfo);
	private:
		//Platform independent function for pausing the game
		inline void pause(const int seconds);
		//Spawn position of the ball
		int startX;
		int startY;
		//Is the ball respawning
		bool respawning;
};
