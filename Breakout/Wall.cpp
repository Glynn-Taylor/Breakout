#include "Wall.hpp"
#include "UIRenderer.hpp"
#include "BoxCollider.hpp"
#include <cstdio>

//A solid wall object that is immovable

		//Constructor
		Wall::Wall(const int xpos, const int ypos, const int width, const int height) : GameObject(xpos,ypos,false), w(width), h(height){
			colour[0] = colour[1] = colour[2] =  1.0f;
			collider = new BoxCollider(width,height,0,*this);
		}
		//Constructor with colour
		Wall::Wall(const int xpos, const int ypos, const int width, const int height, const float col[3]) : GameObject(xpos,ypos,false), w(width), h(height){
			//Assign a collider based on bounds
			collider = new BoxCollider(width,height,0,*this);
			//Store color
			colour[0]=col[0];
			colour[1]=col[1];
			colour[2]=col[2];
			//Ensure null pointer for renderer component
			renderer=NULL;
		}
		//Deconstructor
		Wall::~Wall(){
			//Delete components
			delete(collider);
			if(renderer!=NULL)
				delete(renderer);
		}
		//Called when the gameobject is registered
		void Wall::onStart(){
		}
		//Called every frame by the containing scene
		void Wall::onRender(){
			if(renderer==NULL){
				//glCallList(mesh);
				renderSquare(x-w/2,y-h/2,w,h,colour);
			}else{
				renderer->Render();
			}
		}
		//Called every frame by the containing scene
		void Wall::onUpdate(){
		}
		//Called when the gameobject collides with another collider
		void Wall::onCollide(Collider* other,CollisionInfo collideInfo){
			//Check other object is moving
			if(other->gameObject.rigidbody!=NULL){
				//Check which side collision occured and resolve new velocity
				if(collideInfo.side == XPLUS || collideInfo.side == XMINUS){
					other->gameObject.rigidbody->invertXDirection();
					other->gameObject.x += collideInfo.dx;
				}else{
					other->gameObject.rigidbody->invertYDirection();
					other->gameObject.y += collideInfo.dy;
				}
			}	
		}
		void Wall::onUI(){}
		void Wall::onKeyDown(unsigned char key){}
		void Wall::onKeyUp(unsigned char key){}
