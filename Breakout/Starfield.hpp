#include "GameObject.hpp"
//-Starting z position of stars that have gone past z limit (0)
#define STARS 1000

//Gameobject that displays a starfield effect
class Starfield : public GameObject{
	
	public:
		//Constructor for a starfield, takes the origin x,y,z
		Starfield(const int xpos, const int ypos, const int zpos);
		~Starfield();
		//Generates a list of random coords for stars and stores them in stars
		void onStart();
		//Renders a cube at all coords in stars
		void onRender();
		//Causes the stars to move
		void onUpdate();
		//Unused inherited methods
		void onUI();
		void onKeyDown(unsigned char key);
		void onKeyUp(unsigned char key);
		void onCollide(Collider* other, CollisionInfo info);
	private:
		//Speed at which stars move
		float speed;
		//Position of all stars x,y,z
		float stars[STARS][3];
};
