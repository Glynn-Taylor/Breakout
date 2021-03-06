#include "State.hpp"
class Sprite2D;

// State for displaying the controls to the user (Main menu -> controls state)
// Contains:
// ~Title
// ~Controls list
// ~Back button (controls -> main menu)

class ControlsState : public State
{
	public:
		~ControlsState();
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
	private:
		//Texture handles
		unsigned int testTexture;
		unsigned int redButtonSprite;
		unsigned int greenButtonSprite;
		unsigned int blueButtonSprite;
		//Pointer to animated laser sprite
		Sprite2D* testSprite;	
};
