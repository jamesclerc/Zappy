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
			int getNbRessources(gpc::Entities entity);
			std::vector<int> getNbRessources();
			void draw();
			int getX();
			int getY();
			void setIncantation(bool state);
			void initGroundColor();

		private:
			std::vector<gpc::IEntity *> _entities;
			int _x;
			int _y;
			sf::Color _sol_c;
			void drawEntities();
			sf::Sprite _floor;
			sf::RenderTexture &_window;
			bool _incantation;
	};
}
