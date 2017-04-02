#include "State.hpp"

// State for displaying the main menu
// Contains:
// ~Title
// ~Buttons for 2D, 3D, Controls and exit
// ~Starfield background
class MenuState : public State
{
	public:
		~MenuState();
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
