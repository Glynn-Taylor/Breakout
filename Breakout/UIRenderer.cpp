#ifndef UI_RENDERER
#define UI_RENDERER

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "png_load.hpp"
#include "TextRenderer.hpp"
#include <stdio.h>
#include "Screen.hpp"
#include "Sprite2D.hpp"
#include "Display.hpp"

//Contains helper functions for rendering UI elements

//Terminates the application
void quit(){
	exit(0);
	// glut method of exit so bad, sys for the win
	//glutDestroyWindow(WINID);
}

//Extends isKeyDown for chars
bool isKeyDown(unsigned char key){
	return isKeyDown((int)key);
}
//Returns whether or not a key has been marked as pressed from the Keys array
bool isKeyDown(const int key){
	return Keys[key];
}
//Performs a translate to the center (x axis) of the screen
void centerWidth(bool center){
	
	if(center){
		// Duplicate top of stack transformation matrix and push it to top
		glPushMatrix();
		// Replace top of stack matrix with identity matrix
		//glLoadIdentity();
			glTranslatef(ScreenWidth/2.0f,0.0f,0.0f);
	}else{
		//Remove top of stack matrix
		glPopMatrix();
	}
}
//Performs a translate to the center (y axis) of the screen
void centerHeight(bool center){
	if(center){
		// Duplicate top of stack transformation matrix and push it to top
		glPushMatrix();
		// Replace top of stack matrix with identity matrix
		//glLoadIdentity();
			glTranslatef(0.0f,ScreenHeight/2.0f,0.0f);
	}else{
		//Remove top of stack matrix
		glPopMatrix();
		//glTranslatef(0.0f,-ScreenHeight/2.0f,0.0f);
	}
}
//Sets gl color
void setRenderColor(float col[3]){
	glColor3f(col[0],col[1],col[2]);
}
//Handy template function
extern void renderTemplate(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		//glLoadIdentity();
		glTranslatef(0.0f,0.0f,0.0f);
		glScalef(1.0f,1.0f,1.0f);
		//Dostuff
	glPopMatrix();
}
//Renders a square using the shared display list
void renderSquare(const int x, const int y, const int w, const int h){
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
		//Translate to position and call display list
		glTranslatef(x+w/2.0f,y+h/2.0f,0.0f);
		glScalef(w,h,1.0f);
		glCallList(SquareMesh);
	//Remove pushed matrix
	glPopMatrix();
}
//Calls rendersquare with a custom color
void renderSquare(const int x, const int y, const int w, const int h,const float colour[3]){
	float col[3] = {colour[0], colour[1],colour[2]};
	renderSquare(x,y,w,h);
}
//Calls rendersquare with a custom color
void renderSquare(const int x, const int y, const int w, const int h,float colour[3]){
	glColor3f(colour[0],colour[1],colour[2]);
	renderSquare(x,y,w,h);
}

//Renders a square texture
extern void renderTexture(const int x, const int y, const int w, const int h, unsigned int handle){
		// enable texturing
  		glEnable(GL_TEXTURE_2D); 

		// select which texure to render
  		glBindTexture(GL_TEXTURE_2D, handle); 

		// specify texture coordinates
  		glBegin (GL_QUADS);
  			glTexCoord3f (0.0f,0.0f,0.0f); // lower left corner
  			glVertex2i(x, y);
  			glTexCoord3f (1.0f, 0.0f,0.0f); // lower right corner
  			glVertex2i(x+w, y);
  			glTexCoord3f (1.0f, 1.0f,0.0f); // upper right corner
  			glVertex2i(x+w, y+h);
  			glTexCoord3f (0.0f, 1.0f,0.0f); // upper left corner
  			glVertex2i(x, y+h);
  		glEnd ();

  		glDisable(GL_TEXTURE_2D);
}

//Checks if the mouse position is inside a translated rectangle
bool mouseInsideRect(const int x, const int y, const int w, const int h){
	float matrix[16];
	//Account for matrix translations
	glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
	// 12, 13 ,14 are the xyz translation
	float trueX = matrix[12] + x;
	float trueY = matrix[13] + y;
	//Check if mouse is inside translated coords
	if(MouseX > trueX && MouseX < trueX + w){
		if(MouseY > trueY && MouseY < trueY + h){
			return true;
		}
	}
	return false;
}
//Renders a button and returns true if the mouse is pressed inside of it
extern bool renderButton(const int x, const int y, const int w, const int h, unsigned int buttonHandle=-1, Sprite2D* effect = 0, const char* str = "Unassigned"){
	//Check if mouse is inside of button rect
	bool insideButton = mouseInsideRect(x,y,w,h);	
	glColor3f(1.0f,1.0f,1.0f);
	//Render the background effect
	effect->Render(x-100,y-10,w+200,h+20);
	//Render the button texture
	if(buttonHandle != -1)
		renderTexture(x,y,w,h,buttonHandle);
	//Colour the button text / differently if hovering over
	if(insideButton){
		glColor3f(1.0f,0.5f,0.5f);
		renderText(x,y,w,h,str,true);
	}else{
		glColor3f(1.0f,1.0f,1.0f);
		renderText(x,y,w,h,str,true);
	}
	//Return if LMB pressed and inside
	if(insideButton && LMB){
		LMB=false;
		return true;
	}else{
		return false;
	}
}

//Loads a texture, taken from example in labs
extern unsigned int loadTexture(const char* filename, GLint param = GL_NEAREST)
{
    char* image_buffer = NULL; // the image data
	int width = 0;
	int height = 0;

	// read in the PNG image data into image_buffer
	if (png_load(filename, &width, &height, &image_buffer)==0)
    {
        fprintf(stderr, "Failed to read image texture from %s\n", filename);
        exit(1);
    }

	unsigned int tex_handle = 0;

	// request one texture handle
	glGenTextures(1, &tex_handle); 

	// create a new texture object and bind it to tex_handle
  	glBindTexture(GL_TEXTURE_2D, tex_handle);

  	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);

  	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  	glTexImage2D(GL_TEXTURE_2D, 0, 
				GL_RGBA, width, height, 0,
   		 		GL_RGBA, GL_UNSIGNED_BYTE, image_buffer);

	
	free(image_buffer); // free the image buffer memory
	
	return tex_handle;
}
#endif
