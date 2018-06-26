/*
** EPITECH PROJECT, 2018
** Entity.cpp
** File description:
** Entity cpp
*/

#include "IEntity.hpp"

gpc::IEntity::IEntity(int x, int y, sf::RenderTarget &window) : _x(x), _y(y), _window(window)
{
}

gpc::IEntity::~IEntity()
{
}

gpc::Entities gpc::IEntity::getEntities()
{
	return _idEntity;
}

void gpc::IEntity::setX(int x)
{
	_x = x;
}

void gpc::IEntity::setY(int y)
{
	_y = y;
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