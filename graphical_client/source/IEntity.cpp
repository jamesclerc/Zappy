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

bool gpc::IEntity::is(Entities entity) const
{
	if (entity == _idEntity)
		return true;
	return false;
}