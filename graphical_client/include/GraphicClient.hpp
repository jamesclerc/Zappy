//
// EPITECH PROJECT, 2018
// GraphicClient.hpp
// File description:
// GraphicClient class
//

#pragma once

#include <vector>

#include "Player.h"

namespace gpc {
	class GraphicalClient {
		public:
			~GraphicalClient();
		private:
			std::vector<Player> _players;
			GraphicalClient();
	};
}