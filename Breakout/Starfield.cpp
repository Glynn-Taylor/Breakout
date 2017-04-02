#include "Starfield.hpp"
#include <GL/glut.h>
#include <stdlib.h>
#include <cstdio>

//Gameobject that displays a starfield effect

		//Constructor for a starfield, takes the origin x,y,z
		Starfield::Starfield(const int xpos, const int ypos, const int zpos){
		
		}
		//Deconstructor
		Starfield::~Starfield(){
		}
		//Generates a list of random coords for stars and stores them in stars
		void Starfield::onStart(){
			for(int i = 0; i<STARS; i++){
				// rand % x returns 0-x and has priority over -
				stars[i][0] = rand() % STARS - STARS/2;
				stars[i][1] = rand() % STARS - STARS/2;
				stars[i][2] = -i;
			}
		}
		//Renders a cube at all coords in stars
		void Starfield::onRender(){
			for(int i=0; i<STARS; i++){
				//reset transformation matrix
				glLoadIdentity();
				glTranslatef(stars[i][0],stars[i][1],stars[i][2]);
				//Render
				glutSolidCube(0.5f);
			}
		}
		//Causes the stars to move
		void Starfield::onUpdate(){
			for(int i=0;i<STARS;i++){
				//Moves stars, send them back if they hit a z limit
				stars[i][2] += 2.5f;
				if(stars[i][2]>0){
					stars[i][2] = -STARS;
				}
			}
		}
		void Starfield::onCollide(Collider* other, CollisionInfo info){
		}
		void Starfield::onUI(){}
		void Starfield::onKeyDown(unsigned char key){}
		void Starfield::onKeyUp(unsigned char key){}
