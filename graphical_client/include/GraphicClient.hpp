//
// EPITECH PROJECT, 2018
// GraphicClient.hpp
// File description:
// GraphicClient class
//

#pragma once

#include <vector>

#include "Player.hpp"
#include "Map.hpp"
#include "Communication.hpp"
#include "menu.hpp"

namespace gpc {
	class GraphicClient {
		public:
			static GraphicClient &getInstance();
			GraphicClient(const GraphicClient&) = delete;
			GraphicClient& operator=(const GraphicClient&) = delete;
			~GraphicClient();
			void run();
		private:
			void runMenu();
			void initConnection();
			void mainLoop();
			sf::RenderWindow window;
			static GraphicClient instance
			std::vector<Player> _players;
			GraphicClient();
			Menu _menu;
			Communication _com;
			Map _map;
	};
}