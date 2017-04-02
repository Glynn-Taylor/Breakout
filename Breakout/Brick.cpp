#include "Brick.hpp"
#include "UIRenderer.hpp"
#include "BoxCollider.hpp"
#include "Scoring.hpp"

//A brick that the ball can bounce off of for points (destroys the brick)

//Color values for each row
const float ROWCOLOR[6][3] = {{66.0f/255.0f,72.0f/255.0f,200.0f/255.0f},{72.0f/255.0f,160.0f/255.0f,72.0f/255.0f},{162.0f/255.0f,162.0f/255.0f,42.0f/255.0f},{180.0f,122.0f,48.0f/255.0f},{198.0f/255.0f,108.0f/255.0f,58.0f/255.0f},{200.0f/255.0f,72.0f/255.0f,72.0f/255.0f}};
		//Constructor for putting the brick somewhere
		Brick::Brick(const int xpos, const int ypos, const int width, const int height, const int brickrow) : w(width), h(height), row(brickrow), GameObject(){
			x = xpos;
			y = ypos;
			kinematic=false;
			collider = new BoxCollider(width,height,0,*this);
			//Store the correct row color
			colour[0]=ROWCOLOR[brickrow][0];
			colour[1]=ROWCOLOR[brickrow][1];
			colour[2]=ROWCOLOR[brickrow][2];
		}
		//Deconstructor
		Brick::~Brick(){
			//Add to the player's score based on the brick's row
			Score+=(row<2?1:(row<4?4:7));
			//Delete components
			delete(collider);
			if(renderer!=NULL)
				delete(renderer);
		}
		//Called when the gameobject is registered
		void Brick::onStart(){
			//Tell the renderer to use the correct row colour
			if(renderer!=NULL)
				renderer->setColor(colour);
		}
		//Called every frame by the containing scene
		void Brick::onRender(){
			//Render using the correct method depending on 2D or 3D
			if(renderer!=NULL){
				renderer->Render();
			}else{
				renderSquare(x-w/2,y-h/2,w,h,colour);
			}
		}
		//Called every frame by the containing scene
		void Brick::onUpdate(){
		}
		//Called when the brick collides with another collider, from brickwall
		void Brick::onCollide(Collider* other,CollisionInfo collideInfo){
			//Deflect the other object's rigidbody
			if(other->gameObject.rigidbody!=NULL){
				if(collideInfo.side == XPLUS || collideInfo.side == XMINUS){
					other->gameObject.rigidbody->invertXDirection();
					//Reset the other object's position to outside the collider
					other->gameObject.x += collideInfo.dx;
				}else{
					other->gameObject.rigidbody->invertYDirection();
					//Reset the other object's position to outside the collider
					other->gameObject.y -= collideInfo.dy;
				}
			}	
		}
		void Brick::onUI(){}
		void Brick::onKeyDown(unsigned char key){}
		void Brick::onKeyUp(unsigned char key){}
