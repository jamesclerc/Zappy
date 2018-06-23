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
			Tiles(int x, int y);
			~Tiles();
			gpc::Tiles &getTilesInDirection(gpc::Direction dir);
			void addRessource(IEntity *);
			gpc::IEntity *pickRessource(Entities);
		private:
			std::vector<gpc::IEntity *> _entities;
			int _x;
			int _y;
	};
}