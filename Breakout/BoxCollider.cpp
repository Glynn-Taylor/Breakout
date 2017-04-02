#ifndef BOX_COLLIDER
#define BOX_COLLIDER

#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include <cstdio>

//A rectangular collider that can resolve collisions with other rectangular colliders.

//Constructor
BoxCollider::BoxCollider(const float width, const float height, const float length,GameObject& obj) : Collider(obj){
	w=width;
	h=height;
}
//Generic method first called to determine collider types and resolve specific collider method
CollisionInfo BoxCollider::CollidesWith(Collider const& other) const{
	//Tell other collider to run it's BoxCollider collision function
	return other.CollidesWith(*this);
}

//Specific 'has collided with another box collider' function
CollisionInfo BoxCollider::CollidesWith(BoxCollider const& other) const{
	CollisionInfo collision;
	//implement AABB
	//(Ax,Ay)		(Bx,By)
	//	|------|	  |------|
	//	|      |	  |		 |
	//	|	   |      |		 |
	//	|------|      |------|
	//		  (AX,AY)		(BX,BY)
	collision.collision=false;
	//Use a seperating axis test
	float xDiff = other.Collider::gameObject.x - Collider::gameObject.x;
	float pX = (other.Collider::w/2.0f + Collider::w/2.0f) - (xDiff < 0 ? -xDiff : xDiff);
	//If there is no x difference then we have collided
	if(pX<=0)
		return collision;
	
	float yDiff = other.Collider::gameObject.y - Collider::gameObject.y;
	float pY = (other.Collider::h/2.0f + Collider::h/2.0f) - (yDiff < 0 ? -yDiff : yDiff);
	//If there is no y difference then we have collided
	if(pY<=0)
		return collision;
	//Flag for notifying about collision
	collision.collision=true;
	//Get the hit normal
	//Resolve for smaller xdifference
	if(pX<pY){
		float sx = xDiff < 0 ? -1 : 1;
		collision.side = xDiff < 0 ? XMINUS : XPLUS;
		collision.dx=pX*sx;
		collision.dy=0;
	//Resolve for smaller ydifference
	}else{
		float sy = yDiff < 0 ? -1 : 1;
		collision.side = yDiff < 0 ? YMINUS : YPLUS;
		collision.dy = pY*sy;
		collision.dx=0;
	}
	//Return the result of the test
	return collision;
}
#endif
