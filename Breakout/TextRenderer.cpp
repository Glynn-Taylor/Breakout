#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <deque>
using namespace std;
// Stroke size is 119.05f but bottom descends 33.33 units:
#define STROKE_SIZE 119.05f
#define STROKE_UPPER_SIZE 85.72f

//Renders text in the game world
void renderText(const int x, const int y, const char* text, bool centered = false){
	const float scale =0.25f;
	glMatrixMode(GL_MODELVIEW);
	// Duplicate current transformation matrix and push to top of stack
	glPushMatrix();
		// Replace top of stack matrix with identity matrix (clean transform)
		glLoadIdentity();
		size_t length = strlen(text);
		//Translate with centering
		if(centered==true)
			glTranslatef(x-length/2,y-0.5f,0.0f);
		else
			glTranslatef(x,y,0.0f);
		glScalef(scale,scale,1.0f);
		//Render all characters
		for(size_t i = 0; i<length;i++){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	glPopMatrix();
}
//Renders text in the game world
void renderText(const int x, const int y, const int w, const int h, const char* text, bool centered = false){
	const float padding=2.0f;
	float scale = 1.0f;
	// Duplicate current transformation matrix and put on top of stack
	glPushMatrix();
		//Get length of string
		size_t length = strlen(text);
		unsigned int string_width = 0;
		//Calculate unit width of string
		for(size_t i = 0; i<length;i++){
			string_width+=glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
		}
		//Get padding adjusted width
		float width = w-padding*2;
		//Adjust scale to fit
		if(string_width > width)
			scale = width/string_width;
		//Check height does not break scale
		float height = h-padding*2;
		if(STROKE_SIZE*scale > height){
			scale = height / (STROKE_SIZE*scale);
		}
		//Translate to text start
		glTranslatef(x,y,0.0f);
		//Translate to center
		if(centered==true)
			glTranslatef((w/2-(string_width*scale)/2),h/2-(STROKE_UPPER_SIZE*scale)/2,0.0f);
		else
			glTranslatef(x,y,0.0f);
		//Set scale
		glScalef(scale,scale,1.0f);
		//Render text
		for(size_t i = 0; i<length;i++){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
		}
	//Remove top of stack matrix
	glPopMatrix();
}
//Render a number with preceding 0's
void renderScore(const int x, const int y, const int w, const int h, const int score, const int length = 3){
		//Create buffer for score length + null character
		char * buffer = new char[length+1];
		//Print score to buffer
		snprintf(buffer,sizeof(buffer),"%i",score);
		char * buffer2 = new char[length+1];
		deque<char> str;
		//Set extra zeroes and reverse
		for(int i=0; i<length; i++){
			if(buffer[i]>57 || buffer[i]<48)
				str.push_front('0');	
			else
				str.push_back(buffer[i]);
		}
		delete[] buffer;
		for(int i=0;i<length;i++){
			buffer2[i]=str.at(i);
		}
		//Terminate string
		buffer2[length]='\0';
		//Render the text
		renderText(x,y,w,h,buffer2,true);
		delete[] buffer2;
}
//Render a number
void renderNumber(const int x, const int y, const int w, const int h, const int num){
	//Convert int to num
	char buffer[4];
	snprintf(buffer,sizeof(buffer),"%i",num);
	//Render the text
	renderText(x,y,w,h,buffer,true);
}
//Render a number with some preceding text
void renderScoreNumber(const int x, const int y, const int w, const int h, const int num){
	//Convert int to num
	char buffer[4];
	snprintf(buffer,sizeof(buffer),"%i",num);
	char printout[12];
	//Append Score text
	strcpy(printout,"Score: ");
	strcat(printout,buffer);
	//render the text
	renderText(x,y,w,h,printout,true);
}
