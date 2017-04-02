#include "GameObject.hpp"

class Chunk : public GameObject{
	public:
		void onStart();
		void onRender();
		void onUpdate();
		void onUI();
		void onKeyDown(unsigned char key);

};
