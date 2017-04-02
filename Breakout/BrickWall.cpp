#include "BrickWall.hpp"
#include "UIRenderer.hpp"
#include "BoxCollider.hpp"
#include "Scoring.hpp"
#include "CuboidRenderer.hpp"
#include <cstdio>
		//Constructor for creating a new brickwall
		BrickWall::BrickWall(const int xpos, const int ypos, const int rows, const int columns, const int brickWidth, const int brickHeight, bool is3D){
			//Center the wall based on how many columns/rows and size of a brick
			x=xpos + (brickWidth*columns)/2;
			y=ypos + (brickHeight*rows)/2;
			m_rows=rows;
			m_columns=columns;
			//Create collider covering the whole wall to optimise collisions
			collider = new BoxCollider(brickWidth*columns,brickHeight*rows,0,*this);
			kinematic=false;
			//Generate all of the bricks
			for(int row =0; row<rows;row++){
				for(int column =0; column<columns;column++){
					//Generate a renderer if 3D
					if(is3D){
						Brick* brick = new Brick(xpos+column*brickWidth +brickWidth/2,ypos+row*brickHeight+brickHeight/2,brickWidth,brickHeight,row);
						brick->setRenderer(new CuboidRenderer(brickWidth,brickHeight,10,*brick));
						m_bricks.push_back(brick);	
					}else{
						//Add the new brick to the list
						m_bricks.push_back(new Brick(xpos+column*brickWidth +brickWidth/2,ypos+row*brickHeight+brickHeight/2,brickWidth,brickHeight,row));	
					}
				}
			}
		}
		//Deconstructor
		BrickWall::~BrickWall(){
			//Remove the collider for the wall
			delete(collider);
			//Remove all bricks
			for(int i=0;i<m_bricks.size();i++)
				delete m_bricks[i];
		}
		//Called when the gameobject is registered
		void BrickWall::onStart(){
			//Call start on all bricks
			for(std::vector<Brick*>::iterator i = m_bricks.begin(); i != m_bricks.end(); i++){
				(*i)->onStart();
			}
		}
		//Called every frame by the containing scene
		void BrickWall::onRender(){
			// Call render on all bricks
			for(std::vector<Brick*>::iterator i = m_bricks.begin(); i != m_bricks.end(); i++){
				(*i)->onRender();
			}
			
		}
		//Called every frame by the containing scene
		void BrickWall::onUpdate(){
		}
		//Called when the wall collides with another collider
		void BrickWall::onCollide(Collider* other,CollisionInfo collideInfo){
			//Check which brick the object has collided with
			for(std::vector<Brick*>::iterator i = m_bricks.begin(); i != m_bricks.end();){
				CollisionInfo collision2 = (*i)->collider->CollidesWith(*other);
				//If we have collided with this brick
				if(collision2.collision == true){
					//Call the collision on the brick
					(*i)->onCollide(other,collision2);
					other->gameObject.onCollide((*i)->collider,collision2);
					//i -> destroy();
					delete *i;
					//Remove the brick from the list
					i = m_bricks.erase(i);
					// Check if there is no more bricks left (victory state)
					if(m_bricks.size()==0)
						Victory=true;
				}else{
					i++;
				}
			}
		}
		void BrickWall::onUI(){}
		void BrickWall::onKeyDown(unsigned char key){}
		void BrickWall::onKeyUp(unsigned char key){}
