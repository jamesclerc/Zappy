/*
** EPITECH PROJECT, 2018
** Egg.cpp
** File description:
** Egg.cpp
*/

#include "Egg.hpp"

gpc::Egg::Egg(int x, int y, Entities entity, int eggId) : IEntity(x,y), _id(eggId)
{
	_idEntity = entity;
}

gpc::Egg::~Egg()
{
}

void gpc::Egg::draw()
{

}

void gpc::Egg::update()
{

}