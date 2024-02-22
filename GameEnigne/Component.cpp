#include "Component.h"

Component::Component(CALL_ORDER _order, std::string _name, Object* owner)
	: callOrder(_order)
	, name(_name)
	, owner(owner)
{
}

Component::~Component()
{

}
