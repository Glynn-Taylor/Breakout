#ifndef STATE
#define STATE

#include "TickableObject.hpp"
#include "Scene.hpp"

//Blank class for extending both Scene and TickableObject
class State : public TickableObject, public Scene
{

};
#endif
