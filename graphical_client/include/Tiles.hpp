//
// EPITECH PROJECT, 2018
// Tiles.hpp
// File description:
// Tiles class
//

#pragma once

#include <vector>

#include "IEntity.hpp"

namespace gpc {
	class Tiles {
		public:
			Tiles(int x, int y, sf::Sprite &floor, sf::RenderTexture &window);
			~Tiles();
			void addRessource(IEntity *);
			gpc::IEntity *pickRessource(Entities);
			void draw();
			int getX();
			int getY();
			void setIncantation(bool state);
		private:
			std::vector<gpc::IEntity *> _entities;
			int _x;
			int _y;
			void drawEntities();
			sf::Sprite _floor;
			sf::RenderTexture &_window;
			bool _incantation;
	};
}