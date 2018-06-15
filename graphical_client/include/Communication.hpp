//
// EPITECH PROJECT, 2018
// Communication.hpp
// File description:
// Communication class
//

#pragma once

#include <vector>
#include <string>

namespace gpc {
	class Communication {
		public:
			Communication(std::string ip, int port);
			~Communication();
			void firstConnection();
			void mainLoop();
		private:
			std::string ip;
			int port;
	};
}