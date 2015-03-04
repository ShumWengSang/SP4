#include "Entity.h"


Entity::Entity()
{
	theType = NONE;
}


Entity::~Entity()
{}

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

bool Entity::glRenderObject()
{
	return false;
}

Vector3 Entity::GetScale()
{
	return Vector3(1, 1, 1);
}

void Entity::Update()
{}