#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "MenuState.hpp"
#include "UIRenderer.hpp"
#include "Starfield.hpp"
#include "Screen.hpp"
#include "Sprite2D.hpp"

// State for displaying the main menu
// Contains:
// ~Title
// ~Buttons for 2D, 3D, Controls and exit
// ~Starfield background

using namespace std;
		//Handle for the title texture
		unsigned int testTexture = 0;
		//Handles for button textures
		unsigned int redButtonSprite = 0;
		unsigned int greenButtonSprite = 0;
		unsigned int blueButtonSprite = 0;
		//Pointer to an animated laser sprite
		Sprite2D* testSprite;
		
		//Deconstructor
		MenuState::~MenuState(){
			//Cleanup sprite pointer
			delete(testSprite);
		}
		//Run whenever this state is switched to
		void MenuState::onStart()
		{
			//Load textures
			testSprite = new Sprite2D("./images/laser-effect.png",0.33333f,1.0f,3,1);
			registerGameObject(new Starfield(1,1,1));
			testTexture = loadTexture("./images/BREAKOUT.png");	
			greenButtonSprite = loadTexture("./images/button1.png");
			redButtonSprite = loadTexture("./images/button2.png");	
			blueButtonSprite = loadTexture("./images/button3.png");
			// Call inherited game object initialisation method
			initScene();
		}
		//Handler for key presses
		void MenuState::onKeyDown(unsigned char key)
		{	
			//Shortcuts for buttons
			if(key=='1')
				ScreenState = STATE_ATARI2D;
			if(key=='2')
				ScreenState = STATE_ATARI3D;

			handleKeypress(key);
		}
		void MenuState::onKeyUp(unsigned char key)
		{	
			handleKeypress(key);
		}
		//Runs every frame
		void MenuState::onUpdate()
		{
			//Call to inherited method for updating all gameobjects in the scene
			updateScene();
			//Tick the laser animation
			testSprite->Tick(0.1f);
		}
		//Runs every frame
		void MenuState::onRender()
		{
			//Call to inherited method for rendering all scene objects
			renderScene();
			
		}
		//Runs every frame with orthographic camera set up
		void MenuState::onUI(){
			glColor3f(1.0f,1.0f,1.0f);
			//Translate to screen center
			centerWidth(true);
			centerHeight(true);
				glColor3f(1.0f,1.0f,1.0f);
				//Render title texture
				renderTexture(-300,150,600,200,testTexture);
				glColor3f(1.0f,0.0f,0.0f);
				//Render buttons and check if they are pressed
				if(renderButton(-100,0,200,75,redButtonSprite, testSprite, "Atari2D")){
					ScreenState = STATE_ATARI2D;
				}
				if(renderButton(-100,-100,200,75,redButtonSprite, testSprite, "Atari3D")){
					ScreenState = STATE_ATARI3D;
				}
				if(renderButton(-100,-200,200,75,redButtonSprite, testSprite, "Controls")){
					ScreenState = STATE_CONTROLS;
				}
				if(renderButton(-100,-300,200,75,redButtonSprite, testSprite, " Quit ")){
					quit();
				}
			//Clear translation
			centerHeight(false);
			centerWidth(false);
			
		}
// 

