#ifndef SCENE
#define SCENE

#include "GameObject.hpp"
#include "Renderer.hpp"
#include <vector>
//A container and handler for game objects
class Scene
{
	protected:
		//List of gameobjects that the scene is tracking
		std::vector<GameObject*> sceneObjects;
		//Add a new gameobject to the tracking list and assign a renderer
		void registerGameObject(GameObject* obj, Renderer* render);	
		//Add a new gameobject to the tracking list
		void registerGameObject(GameObject* obj);
		//Call onStart on all tracked gameobjects
		void initScene();
		//Runs every frame
		void updateScene();
		//Runs every frame
		void renderScene();
		//Handles key presses
		void handleKeypress(unsigned char key);
	public:
		//Cleans up gameobjects
		void onDestroy();		
};
#endif
