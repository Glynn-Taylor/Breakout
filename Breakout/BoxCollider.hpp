#include "Collider.hpp"

//A rectangular collider that can resolve collisions with other rectangular colliders.
class BoxCollider : public Collider{
	public:
		//Generic method first called to determine collider types and resolve specific collider method
		CollisionInfo CollidesWith(Collider const& other) const;
		//Specific 'has collided with another box collider' function
		CollisionInfo CollidesWith(BoxCollider const& other) const;
		//Constructor
		BoxCollider(const float width, const float height, const float length,GameObject& obj);
};
