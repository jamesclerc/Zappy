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
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define MAXEVENTS 42
#define funcParse(objet,pointeur)  ((objet).*(pointeur))

namespace gpc {
	class Communication {
		public:
			Communication();
			~Communication();
			int firstConnection();
			void handleCommand(std::string str);
			void setIp(std::string ip);
			void setPort(int port);
			void mainLoop();
		private:
			bool testError(int i);
			void raz(char *str);
			char *getNextLine(int fd);
			void readCommand(int datafd, int pollfd);
			int epollWatch();
			int epollPrepare();
			int socketConnect();
			struct epoll_event *_events;
			std::string _ip;
			int _port;
			int _fd;
			int _pollfd;
	};
}

typedef void (gpc::Communication::*ptrFunc)(std::string);

struct funcs_s {
	std::string str;
	ptrFunc func;
} typedef funcs_t;

static funcs_t tab[1] = {
	{"str", &gpc::Communication::handleCommand}
};