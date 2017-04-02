#include "State.hpp"

// State for displaying 2D atari breakout, uses an orthographic camera with 2D sprite
// gameobjects
class Atari2DState : public State
{
	public:
		//Called when this state is switched to
		void onStart();
		//Handler for key presses
		void onKeyDown(unsigned char key);
		void onKeyUp(unsigned char key);
		//Runs every frame
		void onUpdate();
		void onRender();
		//Runs every frame with orthographic camera set up
		void onUI();
};
