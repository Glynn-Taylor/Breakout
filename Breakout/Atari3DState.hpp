#include "State.hpp"

// State for displaying 3D atari breakout, uses an perspective camera with 3D
// gameobjects
class Atari3DState : public State
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
	private:
		//Current camera position
		float m_cameraX;
		float m_cameraY;
		float m_cameraZ;
		//Is the pitch of the game court currently changing
		bool m_rotatingPitch;
		//Is the yaw of the game court currently changing
		bool m_rotatingYaw;
		//In wireframe mode
		bool m_wireframe;
		
		//Rotate the pitch of the game court
		void rotatePitch(float angle);
		//Rotate the yaw of the game court
		void rotateYaw(float angle);
		//Helper function for registering new walls with the scene
		void createWall(const int x, const int y, const int w, const int h, const float col[3]);
};
