#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "Atari3DState.hpp"
#include "UIRenderer.hpp"
#include "Ball.hpp"
#include "Wall.hpp"
#include "Paddle.hpp"
#include "BrickWall.hpp"
#include "Scoring.hpp"
#include "Screen.hpp"
#include "CuboidRenderer.hpp"
#include <cmath>
#include <stdio.h>
#include <deque>

// State for displaying 3D atari breakout, uses an perspective camera with 3D
// gameobjects

using namespace std;

		//Constants for individual brick width and height
		#define TW  50
		#define TH 32
		#define HTW TW/2
		#define HTH TH/2
		//length of walls in z plane
		#define WALL_DEPTH 100
		//Center coords of the game court in world space
		#define COURT_CENTER_X 500.0f
		#define COURT_CENTER_Y 500.0f

		//Helper function for registering new wall objects
		void Atari3DState::createWall(const int x,const int y,const int w,const int h,const float col[3]){
			//Create the wall without components
			Wall* wall = new Wall(x,y,w,h,col);
			//Add a new renderer component (overrides default sprite rendering)
			wall->setRenderer(new CuboidRenderer(w,h,WALL_DEPTH,*wall));
			wall->renderer->setColor(col);
			//register the wall with the scene
			registerGameObject(wall);
		}
		//Called when this state is switched to
		void Atari3DState::onStart()
		{
			m_cameraX=COURT_CENTER_X;
			m_cameraY=COURT_CENTER_Y;
			m_cameraZ=1000.0f;
			//Set up initial player variables
			Victory=false;
			Score=0;
			Lives=5;
			float red[3] = {200.0f/255.0f,72.0f/255.0f,72.0f/255.0f};
			
			//Create the ball object
			Ball* ball = new Ball(500,TH*2+HTH,10);
			ball->setRenderer(new CuboidRenderer(10,10,10,*ball));
			ball->renderer->setColor(red);
			registerGameObject(ball);
			
			//Create the Paddle
			Paddle* paddle = new Paddle(450,2*TH-10,100,20,10,1000-TW,TW);
			paddle->setRenderer(new CuboidRenderer(100,20,20,*paddle));
			paddle->renderer->setColor(red);
			registerGameObject(paddle);
			//Create the container for all of the bricks
			//Params: TopLeftX, BottomLeftY, Rows, Columns, brickWidth, brickHeight
			registerGameObject(new BrickWall(TW,19*TH,6,18,TW,TH,true));
			
			//Create game court boundary wall ends
			float cyan[3] = {66.0f/255.0f,158.0f/255.0f,130.0f/255.0f};
			createWall(0*TW+HTW,2*TH+HTH,TW,TH,cyan);
			createWall(19*TW+HTW,2*TH+HTH,TW,TH,red);

			//Create game court boundary walls
			float grey[3]= { 142.0f/255.0f,142.0f/255.0f,142.0f/255.0f};
			createWall(0*TW+HTW,3*TH+28*HTH,TW,TH*28,grey);
			createWall(19*TW+HTW,3*TH+28*HTH,TW,TH*28,grey);
			createWall(20*HTW,29*TH+2*HTH,TW*18,TH*2,grey);
			// Call inherited game object initialisation method
			initScene();
		}
		//Handler for key presses
		void Atari3DState::onKeyUp(unsigned char key)
		{
			//Rotate yaw on T
			if(key=='t')
				m_rotatingYaw = !m_rotatingYaw;
			//Rotate Pitch on R
			if(key=='r')
				m_rotatingPitch = !m_rotatingPitch;
			//Toggle wireframe mode on Z
			if(key=='z'){
				if(m_wireframe==false)
					glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				m_wireframe = !m_wireframe;	
			}
			//Detect ESC press (ESC is ascii code 27)
			if(key==27)
				ScreenState = STATE_MENU;
		}
		void Atari3DState::onKeyDown(unsigned char key)
		{
			handleKeypress(key);
		}
		//Runs every frame
		void Atari3DState::onUpdate()
		{
			//Rotate pitch if toggled on
			if(m_rotatingPitch)
				rotatePitch(0.01f);
			//Rotate yaw if toggled on
			if(m_rotatingYaw)
				rotateYaw(0.01f);
			//Call to inherited method for updating all gameobjects in the scene
			updateScene();
			// Check if the player has lost or won and switch state if so
			if(Lives<1)
				ScreenState = STATE_GAMEOVER;	
			if(Victory)
				ScreenState = STATE_VICTORY;
		}
		//Runs every frame
		void Atari3DState::onRender()
		{
			//Camera override
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(90,1000.0f/1088.0f,0.1f,10000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			/*
 *				Eye pos:	 x,y,z
 *				Focus point: x,y,z
 *				Up Vector:	 x,y,z
 *			*/
			gluLookAt(m_cameraX,m_cameraY,m_cameraZ,
						COURT_CENTER_X,COURT_CENTER_Y,0,
					0,1,0);
			
			glColor3f(1.0f,0.0f,1.0f);
			//Call to inherited method for rendering all scene objects
			renderScene();
			glColor3f(1.0f,1.0f,1.0f);
			
			//Render score
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
		void Atari3DState::onUI(){
			//Render some helper text
			renderText(50,50,"'r' rotate pitch, 't' rotate yaw, 'z' wireframe");
		}
		void Atari3DState::rotatePitch(float angle){
		//2D rotation using Y and Z
			//       |
			//       |
			//-------|------Z
			//       |
			//       |Y
			float newZ = cosf(angle) * (m_cameraZ) - sinf(angle) * (m_cameraY-COURT_CENTER_Y);
			float newY = sinf(angle) * (m_cameraZ) + cosf(angle) * (m_cameraY-COURT_CENTER_Y) + COURT_CENTER_Y;
			m_cameraZ = newZ;
			m_cameraY = newY;
		}
		void Atari3DState::rotateYaw(float angle){
		//2D rotation using X and Z
			//       |
			//       |
			//-------|------Z
			//       |
			//       |X
			float newZ = cosf(angle) * (m_cameraZ) - sinf(angle) * (m_cameraX-COURT_CENTER_X);
			float newX = sinf(angle) * (m_cameraZ) + cosf(angle) * (m_cameraX-COURT_CENTER_X) + COURT_CENTER_X;
			m_cameraZ = newZ;
			m_cameraX = newX;
		}

