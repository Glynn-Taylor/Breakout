#include "RigidBody.hpp"
#include "GameObject.hpp"
#include "Collider.hpp"
#include <cmath>

//A component for controlling the movement of a gameobject

//Constructor
RigidBody::RigidBody(GameObject& obj) : gameObject(obj){
	xDirection=0;
	yDirection=0;
	zDirection=0;
	gameObject=obj;
}

//Normalizes the movement velocity
void RigidBody::normalize(){
	float magnitude = sqrt(xDirection*xDirection+yDirection*yDirection+zDirection*zDirection);
	xDirection=xDirection/magnitude;
	yDirection=yDirection/magnitude;
	zDirection=zDirection/magnitude;
}

//Adds a given amount to the magnitude of the velocity
void RigidBody::increaseSpeed(const float amount){
	speed+=amount;
}
//Decreases a given amount to the magnitude of the velocity
void RigidBody::decreaseSpeed(const float amount){
	speed-=amount;
}
//Returns the magnitude of the velocity
float RigidBody::getSpeed(){
	return speed;
}
//Sets the magnitude of the velocity
void RigidBody::setSpeed(const float s){
	speed = (s<0?-s:s);
}
//Sets the velocity's x component
void RigidBody::setDirection(const float x){
	xDirection=x;
	normalize();
}
//Sets the velocity's x and y component
void RigidBody::setDirection(const float x, const float y){
	xDirection=x;
	yDirection=y;
	normalize();
}
//Sets the velocity's x, y and z component
void RigidBody::setDirection(const float x, const float y, const float z){
	xDirection=x;
	yDirection=y;
	zDirection=z;
	normalize();
}
//Runs every frame
void RigidBody::Update(){
	//Move the gameobject by velocity * magnitude
	gameObject.x += xDirection*speed;
	gameObject.y += yDirection*speed;
	gameObject.z += zDirection*speed;
}
//Inverts the x component of the velocity
void RigidBody::invertXDirection(){
	xDirection = -xDirection;
}
//Inverts the y component of the velocity
void RigidBody::invertYDirection(){
	yDirection = -yDirection;
}
//Inverts the y component of the velocity
void RigidBody::invertZDirection(){
	zDirection = -zDirection;
}
//Returns the x component of the velocity
float RigidBody::getYDirection(){
	return yDirection;
}
//Returns the y component of the velocity
float RigidBody::getXDirection(){
	return xDirection;
}
//Returns the z component of the velocity
float RigidBody::getZDirection(){
	return zDirection;
}
