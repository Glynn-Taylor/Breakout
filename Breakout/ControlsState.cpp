#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "ControlsState.hpp"
#include "UIRenderer.hpp"
#include "Starfield.hpp"
#include "Screen.hpp"
#include "Sprite2D.hpp"
#include <cstdio>

// State for displaying the controls to the user (Main menu -> controls state)
// Contains:
// ~Title
// ~Controls list
// ~Back button (controls -> main menu)

using namespace std;

		//Deconstructor, cleans up the sprite used for button backgrounds
		ControlsState::~ControlsState(){
			//Delete any allocated pointers that aren't gameobjects (gameobjects cleaned up by default)
			printf("Cleaning up ControlsState variables...\n");
			delete(testSprite);
		}
		
		//Run whenever this state is switched to
		void ControlsState::onStart()
		{
			//Create an animated laser sprite
			testSprite = new Sprite2D("./images/laser-effect.png",0.33333f,1.0f,3,1);
			//Create a starfield
			registerGameObject(new Starfield(1,1,1));
			//Load textures for buttons
			testTexture = loadTexture("./images/CONTROLS.png");	
			greenButtonSprite = loadTexture("./images/button1.png");
			redButtonSprite = loadTexture("./images/button2.png");	
			blueButtonSprite = loadTexture("./images/button3.png");
			// Call inherited game object initialisation method
			initScene();
		}
		//Handler for key presses
		void ControlsState::onKeyDown(unsigned char key)
		{	
			//Shortcut for going back to the menu
			if(key=='1')
				ScreenState = STATE_MENU;
			handleKeypress(key);
		}
		void ControlsState::onKeyUp(unsigned char key)
		{	
			handleKeypress(key);
		}
		//Runs every frame
		void ControlsState::onUpdate()
		{
			//Call to inherited method for updating all gameobjects in the scene
			updateScene();
			//Tick the laser animation
			testSprite->Tick(0.1f);
		}
		//Runs every frame
		void ControlsState::onRender()
		{
			//Call to inherited method for rendering all scene objects
			renderScene();
		}
		//Runs every frame with orthographic camera set up
		void ControlsState::onUI(){
			//Reset the gl rendering color
			glColor3f(1.0f,1.0f,1.0f);
			
			//Translate to screen center
			centerWidth(true);
			centerHeight(true);
				glColor3f(1.0f,1.0f,1.0f);
				//Render title texture
				renderTexture(-300,150,600,200,testTexture);
				//Render controls text
				renderText(-200,-25, 400,300, "WASD/Arrow keys -> Move",true);
				renderText(-75,-30,150,120,   "ESC -> Back",true);
				renderText(-150,-30,300,240,   "R, T -> Rotate (3D)",true);
				renderText(-150,-60,300,240,   "Z -> Wireframe (3D)",true);
				//Render back button
				glColor3f(1.0f,0.0f,0.0f);
				if(renderButton(-100,-200,200,75,redButtonSprite, testSprite, " Menu ")){
					//On press switch state
					ScreenState = STATE_MENU;
				}
			//Clear translations
			centerHeight(false);
			centerWidth(false);
			
		}
// 

