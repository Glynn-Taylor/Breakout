#ifndef GAME_OBJECT
#define GAME_OBJECT


#include "TickableObject.hpp"
#include "Collider.hpp"
#include "RigidBody.hpp"
#include "Renderer.hpp"

//Abstract class for gameobjects
class GameObject : public TickableObject
{
	public:
		//Default constructor, calls init on components
		GameObject(){
			initComponents();	
		}
		//Constructor with position and movable flag
		GameObject(const int xpos, const int ypos, bool kinem = false){
			x=xpos;
			y=ypos;
			kinematic = kinem;
			initComponents();
		}
		//Moves the gameobject in x,y,z
		void translate(float xt, float yt, float zt){
			x+=xt;
			y+=yt;
			z+=zt;
		}
		//Abstract function for collision handling
		virtual void onCollide(Collider* other, CollisionInfo collideInfo) =0;
		//Getter for iskinematic
		bool isKinematic(){
			return kinematic;
		}
		//Component pointers
		Collider* collider;
		RigidBody* rigidbody;
		Renderer* renderer;
		//Setter for renderer component
		void setRenderer(Renderer* render){
			renderer=render;
		}
		//Position variables
		float x;
		float y;
		float z;
	protected:
		//Flag for whether or not a gameobject can move
		bool kinematic;
	private:
		//Method to insure component pointers are null
		void initComponents(){
			renderer=0;
			collider=0;
			rigidbody=0;
		}
};
#endif
