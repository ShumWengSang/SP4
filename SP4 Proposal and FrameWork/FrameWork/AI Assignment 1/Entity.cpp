#include "Entity.h"


Entity::Entity()
{
	theType = NONE;
}


Entity::~Entity()
{
}

bool Entity::glRenderObject(Vector3 theCameraPosition)
{
	return false;
};


EntityType Entity::getObjectType(void)
{
	return theType;
};


Vector3 Entity::getPosition(void)
 { 
	 std::cout<<"Entered getPos"<<std::endl;
	 Vector3 t; return t;
 };

Vector3 Entity::getDirection()
{
	Vector3 t; return t;
}


bool Entity::operator == (Entity& o)
{
	return bool(getObjectType() == o.getObjectType() && getPosition() == o.getPosition());
}


bool Entity::glRenderObject(int RESOLUTION)
{
	return false;
}

Vector3 Entity::GetScale()
{
	return Vector3(1, 1, 1);
}
