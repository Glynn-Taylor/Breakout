#ifndef COLLIDER
#define COLLIDER

//Constants for the normal vector of a collision
#define XPLUS 0
#define XMINUS 1
#define YPLUS 2
#define YMINUS 3
#define ZPLUS 4
#define ZMINUS 5

//Redefine Gameobject so that can keep a reference back to containing gameobject
class GameObject;
//Redefine boxcolliders for box specific collisions
class BoxCollider;

//Container for storing variables relating to a collision
struct CollisionInfo{
	//Point of collision
	float x,y,z;
	//How far in the collision occured
	float dx,dy,dz;
	//The normal vector constant
	int side;
	bool collision;
};

class Collider{
	public:
		//Containing Gameobject reference
		GameObject& gameObject;
		//Bounding box
		float w,h,l;
		//On construction store gameobject reference
		Collider(GameObject& obj) : gameObject(obj){
		}
		//Abstract collision Checks list
		virtual CollisionInfo CollidesWith(Collider const& other) const  = 0;
		virtual CollisionInfo CollidesWith(BoxCollider const& other) const = 0;
};
#endif
