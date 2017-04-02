#include "State.hpp"
class Sprite2D;

// State for displaying the victory screen
// Contains:
// ~Title
// ~Score
// ~Back button (controls -> main menu)
// ~Quit button

class VictoryState : public State
{
	public:
		~VictoryState();
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
		//Title texture
		unsigned int testTexture;
		//Textures for buttons
		unsigned int redButtonSprite;
		unsigned int greenButtonSprite;
		unsigned int blueButtonSprite;
		//texture for animated laser effect
		Sprite2D* testSprite;	
};
