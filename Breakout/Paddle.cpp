#include "Paddle.hpp"
#include "UIRenderer.hpp"
#include "BoxCollider.hpp"
#include "Colours.hpp"
#include <cmath>
#include <cstdio>

//A moveable paddle object, with attached collider

		//Constructor for creating the paddle
		Paddle::Paddle(const int xpos, const int ypos, const int width, const int height, const float moveSpeed, const int xPlusLimit, const int xMinusLimit) : GameObject(){
			x=xpos;
			y=ypos;
			w=width;
			h=height;
			//Set limits on where the paddle can move
			xPlusBoundary=xPlusLimit;
			xMinusBoundary=xMinusLimit;
			//Attach a collider
			collider = new BoxCollider(width,height,0,*this);
			kinematic=false;
			//Set the movement magnitude
			speed=moveSpeed;
		}
		//Deconstructor
		Paddle::~Paddle(){
			//Cleanup components
			delete(collider);
			if(renderer!=NULL)
				delete(renderer);
		}
		//Called when the gameobject is registered
		void Paddle::onStart(){
		}
		void Paddle::onRender(){
			//Render 2D or 3D depending on if a renderer is attached
			if(renderer!=NULL){
				renderer->Render();
			}else{
				renderSquare(x-w/2,y-h/2,w,h,red);
			}
			
		}
		//Called every frame by the containing scene
		void Paddle::onUpdate(){
			//Move left or right depending on keys pressed, special keys offset by 256
			if(isKeyDown('a') || isKeyDown(GLUT_KEY_LEFT+256)){
				if(x-(w/2)>xMinusBoundary)
					x-=speed;
			}else if(isKeyDown('d') || isKeyDown(GLUT_KEY_RIGHT+256)){
				if(x+w/2<xPlusBoundary)
					x+=speed;
			}
		}
		//Called when the ball collides with another collider
		void Paddle::onCollide(Collider* other,CollisionInfo collideInfo){
			//Reflect any moving objects
			if(other->gameObject.rigidbody!=NULL){
				//Get hit direction 
				if(collideInfo.side == XPLUS || collideInfo.side == XMINUS){
					//If side, invert x and offset back out of this object
					other->gameObject.rigidbody->invertXDirection();
					other->gameObject.x += collideInfo.dx;
				}else{
					//Invert the y direction
					float yDir = -other->gameObject.rigidbody->getYDirection();
					//Get a xdirection between -1 and 1 dependent on where it hit
					//the paddle
					float xDir = (other->gameObject.x - x)/(w/2);
					other->gameObject.rigidbody->setDirection(xDir,yDir);	
					
					other->gameObject.y += collideInfo.dy;
					//Speed up the ball slightly
					other->gameObject.rigidbody->increaseSpeed(0.2f);
				}
			}				
		}
		void Paddle::onUI(){}
		void Paddle::onKeyDown(unsigned char key){
		}
		void Paddle::onKeyUp(unsigned char key){}
