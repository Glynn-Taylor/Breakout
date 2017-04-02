#include "GameObject.hpp"
#include "Brick.hpp"
#include <vector>
//Container class for bricks (controls a 2D array of brick objects)
class BrickWall : public GameObject{
	public:
		//Constructors
		BrickWall(const int xpos, const int ypos, const int rows, const int columns, const int brickWidth, const int brickHeight, bool is3D=false);
		//Deconstructor
		~BrickWall();
		//Called on creation
		void onStart();
		//Called when rendering
		void onRender();
		//Called every frame
		void onUpdate();
		void onUI();
		//Key handling events
		void onKeyDown(unsigned char key);
		void onKeyUp(unsigned char key);
		//Called when a rigidbody enters this collider
		void onCollide(Collider* other, CollisionInfo collideInfo);
	private:
		//Width and height of each brick, number of rows and columns of bricks
		int m_brickWidth, m_brickHeight, m_rows, m_columns;
		//List of created/controlled bricks
		std::vector<Brick*> m_bricks;
};
