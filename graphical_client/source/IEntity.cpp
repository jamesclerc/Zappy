/*
** EPITECH PROJECT, 2018
** Entity.cpp
** File description:
** Entity cpp
*/

#include "IEntity.hpp"

gpc::IEntity::IEntity(int x, int y) : _x(x), _y(y)
{
}

gpc::IEntity::~IEntity()
{
}

bool gpc::IEntity::is(Entities entity) const
{
	if (entity == _idEntity)
		return true;
	return false;
}

int gpc::IEntity::getX()
{
	return _x;
}

int gpc::IEntity::getY()
{
	return _y;
}