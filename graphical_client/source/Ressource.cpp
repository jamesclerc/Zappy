/*
** EPITECH PROJECT, 2018
** Ressource.cpp
** File description:
** Ressource.cpp
*/

#include "Ressource.hpp"

gpc::Ressource::Ressource(int x, int y, Entities entity, sf::RenderTexture &window, sf::Sprite &sprite) : IEntity(x,y, window), _sprite(sprite)
{
	_idEntity = entity;
	switch (entity) {
		case FOOD:
			_pixel_x = 64 * x;
			_pixel_y = 64 * y;
			_sprite.setScale(0.22f, 0.22f);
			break;
		case LINEMATE:
			_pixel_x = 64 * x + 16;
			_pixel_y = 64 * y;
			_sprite.setScale(0.1f, 0.1f);
			break;
		case DERAUMERE:
			_pixel_x = 64 * x + 32;
			_pixel_y = 64 * y;
			_sprite.setScale(0.1f, 0.1f);
			break;
		case SIBUR:
			_pixel_x = 64 * x + 48;
			_pixel_y = 64 * y;
			_sprite.setScale(0.1f, 0.1f);
			break;
		case MENDIANE:
			_pixel_x = 64 * x;
			_pixel_y = 64 * y + 16;
			_sprite.setScale(0.1f, 0.1f);
			break;
		case PHIRAS:
			_pixel_x = 64 * x;
			_pixel_y = 64 * y + 32;
			_sprite.setScale(0.1f, 0.1f);
			break;
		case THYSTAME:
			_pixel_x = 64 * x;
			_pixel_y = 64 * y + 48;
			_sprite.setScale(0.1f, 0.1f);
			break;
	}
}

gpc::Ressource::~Ressource()
{
}

void gpc::Ressource::draw()
{
	_sprite.setPosition(_pixel_x, _pixel_y);
	_window.draw(_sprite);
}

void gpc::Ressource::update()
{

}