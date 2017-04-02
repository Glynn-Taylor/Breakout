#ifdef __APPLE__
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> 
#endif
// Include for cout
#include <stdio.h>
// Include for endl
#include <iostream>
// Include for string
#include <string>

#include "Screen.hpp"
#include "Display.hpp"
#include "GeometryCreator.hpp"

#include "MenuState.hpp"
#include "Atari2DState.hpp"
#include "Atari3DState.hpp"
#include "GameOverState.hpp"
#include "VictoryState.hpp"
#include "ControlsState.hpp"
using namespace std;

// The current state that is running/displaying (menu, 2d breakout etc.)
State *state;

// [Display.hpp]
// Global display lists used to speed up rendering objects by precompiling geometry
size_t SquareMesh;
size_t CubeMesh;

// [Screen.hpp]
// Screen width and height
int ScreenWidth=1000;
int ScreenHeight=1000;
// Mouse coords
float MouseX = 0;
float MouseY=0;
// Whether mouse buttons are down
bool LMB = false;
bool RMB = false;
// Record of which keys are pressed, after 256th are special keys
bool Keys[256+104];
int WINID = 0;
// Allows for transitioning between states, checked each frame for inconsistency
int ScreenState = STATE_MENU;
int CurrentState = STATE_MENU;

// Wrapper for cout
void Debug(string str){
	cout << str << endl;
}

// Called every few frames a key is down, by glut
void onKeyDown(const int key,int,int){
	state->onKeyDown(key);
	Keys[key]=true;
}

// Wrapper for on key down that converts a char key into it's ascii value
void onKeyDown(unsigned char key, int, int)
{
	onKeyDown((int)key,0,0);
}

//Called when a key is released, by glut
void onKeyUp(const int key, int, int){
	state->onKeyUp(key);
	Keys[key]=false;
}

// Wrapper for on key up that converts a char key into it's ascii value
void onKeyUp(unsigned char key, int ,int){
	onKeyUp((int)key,0,0);	
}

// Wrapper for on key down for handling special keys, special keys are offset by 256
void onSpecialKeyDown(const int key, int, int){
	onKeyDown(key+256,0,0);
}

//Wrapper for on key up for handling special keys, special keys are offset by 256
void onSpecialKeyUp(const int key, int, int){
	onKeyUp(key+256,0,0);
}

// Switches state when current state and screen state are not consistent
void SwitchState(){
	//Allow state to cleanup pre-delete
	state->onDestroy();
	printf("Deleting current state...\r");
	//Delete state calling it's deconstructor
	delete(state);
	//Create a new state based on the set screenstate
	switch(ScreenState){
		case STATE_MENU:
			state = new MenuState();
			break;
		case STATE_ATARI2D:
			state = new Atari2DState();
			break;
		case STATE_ATARI3D:
			state = new Atari3DState();
			break;
		case STATE_GAMEOVER:
			state = new GameOverState();
			break;
		case STATE_VICTORY:
			state = new VictoryState();
			break;
		case STATE_CONTROLS:
			state = new ControlsState();
			break;
	}
	printf("Deleting current state... Success!\n");
	printf("Initialising new state...\r");
	//Call new state's init
	state->onStart();
	//Ensure consistency
	CurrentState=ScreenState;
	printf("Initialising new state... Success!\n");
	//Force not being in wireframe mode (for menus etc.)
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

//Runs each frame
void update(){
	//Update the current state
	state->onUpdate();
	//Check state consistency to allow for state changes
	if(CurrentState!=ScreenState){
		SwitchState();
	}
	//Refresh the display
	glutPostRedisplay();
}

//Runs each frame
void display()
{
	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT); 
	
	///////////////
	//Perspective//
	///////////////
	glColor3f(1.0f,1.0f,1.0f);
	//Set Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set up camera, performing float conversion before division
	gluPerspective(60,(1.0f*ScreenWidth)/ScreenHeight,1,1000);
	//Render
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		state->onRender();
	
	///////////////
	//	   UI	 //
	///////////////	  		
	//Setup UI camera
	glColor3f(1.0f,1.0f,1.0f);
	//Set camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,ScreenWidth,0,ScreenHeight);
	// Render
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		state->onUI();
	//Swap back buffer (double buffering)
	glutSwapBuffers(); 
}

//Called on screen resize
void reshape(int w, int h)
{
	//Redo viewport
	glViewport(0,0,w,h);
	//Set new resolution
	ScreenWidth=w;
	ScreenHeight=h;
	//Redraw
	glutPostRedisplay();
}

// Called on mouse movement, tracks the cursor position
void mouseMove(int x, int y){
	MouseX = x;
	// Track y from bottom to top
	MouseY = ScreenHeight - y;
}

//Called whenever a mousebutton is presssed, tracks LMB and RMB
void mouseDown(int button, int state, int x, int y){
	
	if(button == GLUT_LEFT_BUTTON){
		LMB = (state == GLUT_DOWN ? true : false);	
	}else if(button == GLUT_RIGHT_BUTTON){
		RMB = (state == GLUT_DOWN ? true : false);
	}
}

//Precompile square and cube geometry
void createMeshes(){
	// Refers to GeometryCreator
	SquareMesh = makeSquare();
	CubeMesh = makeCube();
}

// Called as the program launches
void init()
{
	//Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//Precompile meshes
	createMeshes();
	//Set the initial state to menu and initialise it
	state = new MenuState();
	state->onStart();
}

// Not really necessary as heap free'd on exit
void onClose(){
	delete state;
}

// Program entry point, handles glut initialisation
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); 
	// Setup window properties
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH); 
	glutInitWindowSize(1080, 720); 
	glutInitWindowPosition(50, 50);
	// Create the window
	WINID = glutCreateWindow("1304879: CS324 - Breakout"); 
	// glut functions -> functions
	glutDisplayFunc(display);
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	glutSpecialFunc(onSpecialKeyDown);
	glutSpecialUpFunc(onSpecialKeyUp);
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutPassiveMotionFunc(mouseMove);	
	glutMouseFunc(mouseDown);
	//Last init
	init();
	//Go into glut main loop (runs all glut functions)
	glutMainLoop();
	//On exit
	onClose();
	return 0; 
}
