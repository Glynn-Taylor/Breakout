#ifndef RIGID_BODY
#define RIGID_BODY

class GameObject;

//A component for controlling the movement of a gameobject
class RigidBody{
	public:
		//Gameobject reference
		GameObject& gameObject;
		//Constructor
		RigidBody(GameObject& obj);
		//Adds a given amount to the magnitude of the velocity
		void increaseSpeed(const float amount);
		//Subtract a given amount to the magnitude of the velocity
		void decreaseSpeed(const float amount);
		//Sets the x component of the velocity
		void setDirection(const float x);
		//Sets the x,y components of the velocity
		void setDirection(const float x, const float y);
		//Sets the velocity
		void setDirection(const float x, const float y, const float z);
		//Sets the magnitude of the velocity
		void setSpeed(const float s);
		//Runs every frame
		void Update();
		//Inverts the x component of the velocity
		void invertXDirection();
		//Inverts the y component of the velocity
		void invertYDirection();
		//Inverts the z component of the velocity
		void invertZDirection();
		float getSpeed();
		//Returns the x component of the velocity
		float getXDirection();
		//Returns the y component of the velocity
		float getYDirection();
		//Returns the z component of the velocity
		float getZDirection();

	private:
		//Normalizes the movement velocity
		void normalize();
		//The x,y,z components of the velocity
		float xDirection,yDirection,zDirection;
		//The magnitude of the velocity
		float speed;
};
#endif
