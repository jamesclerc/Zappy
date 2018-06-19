//
// EPITECH PROJECT, 2018
// Communication.hpp
// File description:
// Communication class
//

#pragma once

#include <vector>
#include <string>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/epoll.h>

namespace gpc {
	class Communication {
		public:
			Communication(std::string ip, int port);
			~Communication();
			void firstConnection();
			void mainLoop();
		private:
			int epoll_watch(int pollfd, int datafd);
			int epoll_prepare(int datafd);
			int socket_listen(uint16_t port, int backlog);
			std::string _ip;
			int _port;
	};
}