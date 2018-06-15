//
// EPITECH PROJECT, 2018
// Map.hpp
// File description:
// Map class
//

#pragma once

#include <vector>

#include "Tiles.hpp"

namespace gpc {
	class Map {
		public:
		Map();
		~Map();
		private:
		std::vector<std::vector<Tiles *>> map;
	};
}