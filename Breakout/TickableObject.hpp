#ifndef TICKABLE_OBJECT
#define TICKABLE_OBJECT

//Interface for activities that occur every frame
class TickableObject
{
	public:
		//Abstract function for calling when the object is introduced
		virtual void onStart() = 0;
		//Abstract function for calling every frame
		virtual void onRender() = 0;
		//Abstract function for calling every frame
		virtual void onUpdate() = 0;
		//Abstract function for calling every frame
		virtual void onUI() = 0;
		//Abstract function for keyboard input handling
		virtual void onKeyDown(unsigned char key) = 0;
		virtual void onKeyUp(unsigned char key)=0;
};
#endif
