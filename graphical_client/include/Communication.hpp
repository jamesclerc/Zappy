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
	class GraphicClient;
	class Communication {
		public:
			Communication(GraphicClient &client);
			~Communication();
			int firstConnection();
			void handleCommand(std::string str);
			void handleTgt(std::string str);
			void handleMsz(std::string str);
			void handleBct(std::string str);
			void handlePnw(std::string str);
			void handleNeg(std::string str);
			void handleHeg(std::string str);
			void handlePic(std::string str);
			void handleRsp(std::string str);
			void handlePdr(std::string str);
			void handlePgt(std::string str);
			void handlePet(std::string str);
			void handlePmf(std::string str);
			void handlePtu(std::string str);
			void handlePbc(std::string str);
			void handlePie(std::string str);
			void handleEdi(std::string str);
			void handlePdi(std::string str);
			void handleSeg(std::string str);
			void handleWelcome(std::string str);
			void setIp(std::string ip);
			void setPort(int port);
			void mainLoop();
		private:
			bool testError(int i);
			void handleBct2(int x, int y, std::string str);
			void raz(char *str);
			char *getNextLine(int fd);
			void readCommand(int datafd, int pollfd);
			int epollWatch();
			int epollPrepare();
			int socketConnect();
			GraphicClient &_client;
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

static funcs_t tab[19] = {
	{"tgt", &gpc::Communication::handleTgt},
	{"msz", &gpc::Communication::handleMsz},
	{"bct", &gpc::Communication::handleBct},
	{"pnw", &gpc::Communication::handlePnw},
	{"neg", &gpc::Communication::handleNeg},
	{"heg", &gpc::Communication::handleHeg},
	{"pic", &gpc::Communication::handlePic},
	{"rsp", &gpc::Communication::handleRsp},
	{"pdr", &gpc::Communication::handlePdr},
	{"pgt", &gpc::Communication::handlePgt},
	{"pet", &gpc::Communication::handlePet},
	{"pmf", &gpc::Communication::handlePmf},
	{"ptu", &gpc::Communication::handlePtu},
	{"pbc", &gpc::Communication::handlePbc},
	{"pie", &gpc::Communication::handlePie},
	{"edi", &gpc::Communication::handleEdi},
	{"pdi", &gpc::Communication::handlePdi},
	{"seg", &gpc::Communication::handleSeg},
	{"WELCOME", &gpc::Communication::handleWelcome}
};