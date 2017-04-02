#include "Ball.hpp"
#include "UIRenderer.hpp"
#include "BoxCollider.hpp"
#include <cstdio>
#include "Colours.hpp"
#include "Scoring.hpp"
#include <ctime>
#include<io.h>
#include "SpriteRenderer.hpp"
//Delay whenever the ball goes off the game court
const int RESPAWN_TIME =  1;
		//Platform independent functions for pausing the game whilst respawning
		#if defined(__WIN32__)||defined(_WIN32)||defined(WIN32)||defined(__WINDOWS__)
			#include <windows.h>
			inline void Ball::pause(const int seconds){
				Sleep(seconds*1000);
			}
		#else
			#include <unistd.h>
			inline void Ball::pause(const int seconds){
				usleep(seconds*1000000);
			}
		#endif

		//Constructor for putting the ball somewhere
		Ball::Ball(const int xpos, const int ypos, const int width){
			//Set variables
			size=width;
			x=xpos;
			y=ypos;
			startX=x;
			startY=y;
			kinematic=true;
			//Attach a collider component
			collider = new BoxCollider(width,width,0,*this);
			//Attach a rigidbody component
			rigidbody = new RigidBody(*this);
			//Set the initial velocity vector
			rigidbody->setDirection(1,1,0);
			//Set the velocity magnitude
			rigidbody->setSpeed(5);
		}
		//Ball deconstructor
		Ball::~Ball(){
			//Delete components
			delete(collider);
			delete(rigidbody);
			if(renderer!=NULL)
				delete(renderer);
		}
		//Called when the gameobject is registered
		void Ball::onStart(){
		}
		//Called every frame by the containing scene
		void Ball::onRender(){
			if(respawning==false)
			//Render with renderer if available, otherwise use default 2D rendering
				if(renderer!=NULL)
					renderer->Render();
				else
					renderSquare(x-size/2,y-size/2,size,size,red);
		}
		//Called every frame by the containing scene
		void Ball::onUpdate(){
			//Respawn the ball
			if(respawning==true){
					//Wait here for a set time
					pause(RESPAWN_TIME);
					//Respawn and reset position
					respawning=false;
					y=startY;
					x=startX;
			//Update the ball
			}else{
				//Add velocity to the position
				rigidbody->Update();
				//Check for off screen
				if(y<0 || x<0 || x > 1000){
					//Respawn the ball
					Lives--;
					respawning=true;
					//Redirect the ball for after respawn
					if(rigidbody->getYDirection()<0)
						rigidbody->invertYDirection();
				}
			}
		}
		//Called when the ball collides with another collider
		void Ball::onCollide(Collider* other, CollisionInfo collideInfo){
			
		}
		void Ball::onUI(){}
		void Ball::onKeyDown(unsigned char key){}
		void Ball::onKeyUp(unsigned char key){}
