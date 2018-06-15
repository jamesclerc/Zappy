//
// EPITECH PROJECT, 2018
// Tiles.hpp
// File description:
// Tiles class
//

#pragma once

#include <vector>

#include "Player.hpp"
#include "IEntity.hpp"

namespace gpc {
	class Tiles {
		public:
			Tiles(int x, int y);
			~Tiles();
			Tiles getTilesInDirection(Direction dir);
		private:
			Graphic _graph;
			std::vector<IEntity *> _entities;
			int _x;
			int _y;
	};
}