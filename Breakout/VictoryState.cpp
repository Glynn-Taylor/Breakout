#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "VictoryState.hpp"
#include "UIRenderer.hpp"
#include "Starfield.hpp"
#include "Screen.hpp"
#include "Scoring.hpp"
#include "Sprite2D.hpp"
#include <cstdio>

// State for displaying the victory screen
// Contains:
// ~Title
// ~Score
// ~Back button (controls -> main menu)
// ~Quit button

using namespace std;
		//Deconstructor
		VictoryState::~VictoryState(){
			printf("Cleaning up VictoryState variables...\n");
			delete(testSprite);
		}
		//Called when this state is switched to
		void VictoryState::onStart()
		{
			//Create textures
			testSprite = new Sprite2D("./images/laser-effect.png",0.33333f,1.0f,3,1);
			registerGameObject(new Starfield(1,1,1));
			testTexture = loadTexture("./images/victory.png");	
			greenButtonSprite = loadTexture("./images/button1.png");
			redButtonSprite = loadTexture("./images/button2.png");	
			blueButtonSprite = loadTexture("./images/button3.png");
			// Call inherited game object initialisation method
			initScene();
		}
		//Key input handler
		void VictoryState::onKeyDown(unsigned char key)
		{	
			//Shortcut for button press
			if(key=='1')
				ScreenState = STATE_MENU;
			handleKeypress(key);
		}
		void VictoryState::onKeyUp(unsigned char key)
		{	
			handleKeypress(key);
		}
		//Runs every frame
		void VictoryState::onUpdate()
		{
			//Call to inherited method for updating all gameobjects in the scene
			updateScene();
			//Tick the laser animation
			testSprite->Tick(0.1f);
		}
		void VictoryState::onRender()
		{
			//Call to inherited method for rendering all scene objects
			renderScene();
			
		}
		//Runs every frame with orthographic camera set up
		void VictoryState::onUI(){
			glColor3f(1.0f,1.0f,1.0f);
			//Translate to screen center		
			centerWidth(true);
			centerHeight(true);
				glColor3f(1.0f,1.0f,1.0f);
				//Render title texture
				renderTexture(-300,150,600,200,testTexture);
				//Render player score
				renderScoreNumber(-75,60,150,90,Score);
				glColor3f(1.0f,0.0f,0.0f);
				//Render buttons and switch state on press
				if(renderButton(-100,-50,200,75,redButtonSprite, testSprite, " Menu ")){
					ScreenState = STATE_MENU;
				}
				if(renderButton(-100,-150,200,75,redButtonSprite, testSprite, " Quit ")){
					quit();
				}
			//Clear translations
			centerHeight(false);
			centerWidth(false);
			
		}
// 

