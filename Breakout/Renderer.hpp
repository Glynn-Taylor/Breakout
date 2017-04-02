#ifndef RENDERER
#define RENDERER

class GameObject;

//Component that defines it's own rendering technique for a gameobject to call
class Renderer{
	public:
		//Gameobject reference
		GameObject& gameObject;
		//Bounding box
		float w,h,l;
		//Default constructor assigns gameobject
		Renderer(GameObject& obj) : gameObject(obj){
		}
		//Abstract render function
		virtual void Render()= 0;
		
		//Sets the color variable
		void setColor(float color[3]){
			m_color[0]=color[0];
			m_color[1]=color[1];
			m_color[2]=color[2];
		}
		//Sets the color variable using a const array
		void setColor(const float color[3]){
			m_color[0]=color[0];
			m_color[1]=color[1];
			m_color[2]=color[2];
		}
	protected:
		//Color to use when rendering
		float m_color[3];
};
#endif
