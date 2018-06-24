/*
** EPITECH PROJECT, 2018
** Egg.cpp
** File description:
** Egg.cpp
*/

#include "Egg.hpp"

gpc::Egg::Egg(int x, int y, Entities entity, int eggId) : IEntity(x,y), _id(eggId), _hatching(false)
{
	_idEntity = entity;
}

gpc::Egg::~Egg()
{
}

int gpc::Egg::getId()
{
	return _id;
}

void gpc::Egg::hatching()
{
	_hatching = true;
}

void gpc::Egg::draw()
{

}

void gpc::Egg::update()
{

}