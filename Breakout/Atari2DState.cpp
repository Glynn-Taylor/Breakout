#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "Atari2DState.hpp"
#include "UIRenderer.hpp"
#include "Ball.hpp"
#include "Wall.hpp"
#include "Paddle.hpp"
#include "BrickWall.hpp"
#include "Scoring.hpp"
#include "Screen.hpp"
#include <stdio.h>
#include <deque>

// State for displaying 2D atari breakout, uses an orthographic camera with 2D sprite
// gameobjects

using namespace std;

//The current score the player has achieved, implements Scoring.hpp
int Score;
//The amount of lives the player has left before they lose
int Lives;
//Has all blocks been destroyed
bool Victory;

		//Constants for individual brick width and height
		#define TW  50
		#define TH 32
		#define HTW TW/2
		#define HTH TH/2
		
		//Called when this state is switched to
		void Atari2DState::onStart()
		{
			//Set up initial player variables
			Victory=false;
			Score=0;
			Lives=5;
			//Create game court boundary walls
			float grey[3]= { 142.0f/255.0f,142.0f/255.0f,142.0f/255.0f};
			registerGameObject(new Wall(0*TW+HTW,3*TH+28*HTH,TW,TH*28,grey));
			registerGameObject(new Wall(19*TW+HTW,3*TH+28*HTH,TW,TH*28,grey));
			registerGameObject(new Wall(20*HTW,29*TH+2*HTH,TW*18,TH*2,grey));
			//Create game court boundary wall ends
			float cyan[3] = {66.0f/255.0f,158.0f/255.0f,130.0f/255.0f};
			float red[3] = {200.0f/255.0f,72.0f/255.0f,72.0f/255.0f};
			registerGameObject(new Wall(0*TW+HTW,2*TH+HTH,TW,TH,cyan));
			registerGameObject(new Wall(19*TW+HTW,2*TH+HTH,TW,TH,red));
			//Create the ball object
			registerGameObject(new Ball(500,TH*2+HTH,10));
			//Create the Paddle
			registerGameObject(new Paddle(450,2*TH-10,100,20,10,1000-TW,TW));
			//Create the container for all of the bricks
			//Params: TopLeftX, BottomLeftY, Rows, Columns, brickWidth, brickHeight
			registerGameObject(new BrickWall(TW,19*TH,6,18,TW,TH));
			// Call inherited game object initialisation method
			initScene();
		}
		//Handler for key presses
		void Atari2DState::onKeyDown(unsigned char key)
		{
			//Shortcut for going back to the menu
			if(key==27)
				ScreenState=STATE_MENU;
			handleKeypress(key);
		}
		void Atari2DState::onKeyUp(unsigned char key)
		{
			handleKeypress(key);
		}
		//Runs every frame
		void Atari2DState::onUpdate()
		{
			//Call to inherited method for updating all gameobjects in the scene
			updateScene();
			// Check if the player has lost or won and switch state if so
			if(Lives<1)
				ScreenState = STATE_GAMEOVER;	
			if(Victory)
				ScreenState = STATE_VICTORY;
		}
		//Runs every frame
		void Atari2DState::onRender()
		{
			//Camera override
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0,1000,0,1088);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//Reset gl rendering color
			glColor3f(1.0f,0.0f,1.0f);
			//Call to inherited method for rendering all scene objects
			renderScene();
			glColor3f(1.0f,1.0f,1.0f);
			//Render player score
			renderScore(3*TW,31*TH,6*TW,3*TH,Score,3);
			
			//Render lives
			char buffer[4];
			//Int to string conversion
			snprintf(buffer,sizeof(buffer),"%i",Lives);
			renderText(8*TW,31*TH,6*TW,3*TH,buffer,true);
			//Render number from the original atari breakout, I presume it meant player number?
			renderText(12*TW,31*TH,6*TW,3*TH,"1",true);
		}
		//Runs every frame with orthographic camera set up
		void Atari2DState::onUI()
		{
		} 

