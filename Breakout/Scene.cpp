#include "Scene.hpp"
#include <cstdio>

//A container and handler for game objects
		
		//Cleans up gameobjects
		void Scene::onDestroy(){
			//Delete all gameobjects in the scene
			printf("Clearing up GameObjects...\r");
			for (std::vector<GameObject*>::iterator it = sceneObjects.begin() ; it != sceneObjects.end(); it++)
   			{
     			delete *it;
   			}
			//Clear the gameobject list
			printf("Cleaing up GameObjects... Sucess!\n");
   			sceneObjects.clear();	
		}
		//Add a new gameobject to the tracking list
		void Scene::registerGameObject(GameObject* obj){
			sceneObjects.push_back(obj);
		}
		//Add a new gameobject to the tracking list and assign a renderer
		void Scene::registerGameObject(GameObject* obj, Renderer* render){
			obj->renderer = render;
			registerGameObject(obj);
		}
			
		//Call onStart on all tracked gameobjects
		void Scene::initScene(){
			std::vector<GameObject*>::iterator itr;
			for(itr=sceneObjects.begin();itr < sceneObjects.end();itr++){
				//Short form of
				//GameObject* ptrGameObject = *itr;
				//ptrGameobject->onStart()
				(*itr)->onStart();
			}
			
		}
		//Runs every frame
		void Scene::updateScene(){
			//printf("updating scene\n");
			std::vector<GameObject*>::iterator itr;
			for(itr=sceneObjects.begin();itr < sceneObjects.end();itr++){
				//Collision detect if is moving
				if((*itr)->isKinematic()){
					//Check moving object against all collideable objects
					std::vector<GameObject*>::iterator itr2;
					for(itr2=sceneObjects.begin();itr2 < sceneObjects.end();itr2++){
						if(itr!=itr2 && (*itr2)->collider!=0){
							//Run collision test
							CollisionInfo collideInfo = ((*itr)->collider->CollidesWith(*((*itr2)->collider)));
							if(collideInfo.collision==true){
								//Call collision methods
								(*itr)->onCollide((*itr2)->collider,collideInfo);
								(*itr2)->onCollide((*itr)->collider,collideInfo);
							}
						}
					}
				}
				//Call update on each gameobject
				(*itr)->onUpdate();
				
			}
		}
		//Runs every frame
		void Scene::renderScene(){
			std::vector<GameObject*>::iterator itr;
			//Call on render on every gameobject
			for(itr=sceneObjects.begin();itr < sceneObjects.end();itr++){
				(*itr)->onRender();
			}
		}
		//Handles key presses
		void Scene::handleKeypress(unsigned char key){
			std::vector<GameObject*>::iterator itr;
			//Call onKeyDown on all gameobjects
			for(itr=sceneObjects.begin();itr < sceneObjects.end();itr++){
				(*itr)->onKeyDown(key);
			}
		}
