#include "png_load.hpp"
#include "TextRenderer.hpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
class Sprite2D;

//Contains helper functions for rendering UI elements

//Terminates the application
void quit();
//Extends isKeyDown for chars
bool isKeyDown(unsigned char key);
//Returns whether or not a key has been marked as pressed from the Keys array
bool isKeyDown(const int key);
//Performs a translate to the center (x axis) of the screen
void centerWidth(bool center);
//Performs a translate to the center (y axis) of the screen
void centerHeight(bool center);
//Sets gl color
void setRenderColor(float col[3]);
//Checks if the mouse position is inside a translated rectangle
bool mouseInsideRect(const int x, const int y, const int w, const int h);
//Handy template function
extern void renderTemplate();
//Renders a square using the shared display list
void renderSquare(const int x, const int y, const int w, const int h);
//Calls rendersquare with a custom color
void renderSquare(const int x, const int y, const int w, const int h, const float colour[3]);
//Calls rendersquare with a custom color
void renderSquare(const int x, const int y, const int w, const int h, float colour[3]);
//Renders a square texture
extern void renderTexture(const int x, const int y, const int w, const int h, unsigned int handle);
//Renders a button and returns true if the mouse is pressed inside of it
extern bool renderButton(const int x, const int y, const int w, const int h, unsigned int buttonHandle=-1, Sprite2D* effectHandle = 0, const char* str = "Unassigned");
//Loads a texture, taken from example in labs
extern unsigned int loadTexture(const char* filename, GLint param = GL_NEAREST);
