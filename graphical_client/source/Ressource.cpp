/*
** EPITECH PROJECT, 2018
** Ressource.cpp
** File description:
** Ressource.cpp
*/

#include "Ressource.hpp"

gpc::Ressource::Ressource(int x, int y, Entities entity) : IEntity(x,y)
{
	_idEntity = entity;
}

gpc::Ressource::~Ressource()
{
}

void gpc::Ressource::draw()
{

}

void gpc::Ressource::update()
{

}