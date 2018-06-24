/*
** EPITECH PROJECT, 2018
** Communication.cpp
** File description:
** Communication cpp
*/

#include "Communication.hpp"
#include "GraphicClient.hpp"


gpc::Communication::Communication(GraphicClient &client) : _client(client)
{
	_events = (struct epoll_event *)calloc(MAXEVENTS, sizeof(struct epoll_event));
}

gpc::Communication::~Communication()
{
}

void gpc::Communication::setIp(std::string ip)
{
	_ip = ip;
}

void gpc::Communication::setPort(int port)
{
	_port = port;
}

int gpc::Communication::firstConnection()
{
	if (socketConnect() == -1)
		return -1;
	if (epollPrepare() == -1)
		return -1;
	return (0);
}

bool gpc::Communication::testError(int i)
{
	if ((_events[i].events & EPOLLERR)
	|| (_events[i].events & EPOLLHUP)
	|| !(_events[i].events & EPOLLIN)) {
		close (_events[i].data.fd);
		return true;
	}
	return false;
}

void gpc::Communication::mainLoop()
{
	int n = epoll_wait (_pollfd, _events, MAXEVENTS, -1);
	for (int i = 0; i < n; i++) {
		if (testError(i))
			continue;
		else {
			readCommand(_events[i].data.fd, _pollfd);
		}
	}
}

void gpc::Communication::raz(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0') {
		str[i] = 0;
		i++;
	}
}

char *gpc::Communication::getNextLine(int fd)
{
	int size = 1;
	char buffer[512];
	int mallocsize = 1;
	char *result = (char *)malloc(sizeof(char) * mallocsize + 1);

	if (result == NULL)
		return (NULL);
	result[0] = 0;
	while (result && size > 0) {
		raz(buffer);
		size = read(fd, buffer, 1);
		if (size > 0) {
			mallocsize += 1;
			buffer[size] = '\0';
			result = (char *)(realloc(result, mallocsize));
			strcat(result, buffer);
		}
		else
			return (NULL);
		if (size > 0 && buffer[0] == '\n')
			break;
	}
	result[strlen(result) - 1] = 0;
	return (result);
}

void gpc::Communication::handleCommand(std::string str)
{
	for (int i = 0; i < 3 ; i++)
	{
		if (str.compare(tab[i].str) == 0)
			funcParse(*this, tab[i].func)(str);
	}
}

void gpc::Communication::handleTgt(std::string str)
{
	std::string::size_type sz;

	_client.setTimer(std::stoi(str, &sz));
}

void gpc::Communication::handleMsz(std::string str)
{
	size_t pos = 0;
	std::string token;
	std::string::size_type sz;

	pos = str.find(" ");
	token = str.substr(0, pos);
	str.erase(0, pos + 1);
	_client.constructMap(std::stoi(token, &sz), std::stoi(str, &sz));
}

void gpc::Communication::handleBct(std::string str)
{
	size_t pos = 0;
	std::string token;
	std::string firstTok;
	std::string::size_type sz;

	pos = str.find(" ");
	token = str.substr(0, pos);
	firstTok = token;
	str.erase(0, pos + 1);
	handleBct2(std::stoi(firstTok, &sz), std::stoi(token, &sz), str);
}

void gpc::Communication::handleBct2(int x , int y, std::string str)
{
	size_t pos = 0;
	std::string token;
	std::string firstTok;
	std::string delimiter = " ";
	std::string::size_type sz;

	std::vector<int> ressources;
	for (int i = 0; i < 6; i++)
	{
		pos = str.find(delimiter);
		token = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		ressources.push_back(std::stoi(token, &sz));
	}
	ressources.push_back(std::stoi(str, &sz));
	_client.completeTiles(x, y, ressources);
}

void gpc::Communication::readCommand(int datafd, int pollfd)
{
	char *cmd = getNextLine(datafd);

	if (cmd != NULL) {
		handleCommand(std::string(cmd));
	}
	else {
		epoll_ctl(_pollfd, EPOLL_CTL_DEL, datafd, NULL);
		shutdown(datafd, SHUT_RDWR);
	}
}

int gpc::Communication::socketConnect()
{
	struct protoent *pe;
	struct sockaddr_in address;

	pe = getprotobyname("TCP");
	if (!pe)
		return(-1);
	_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (_fd == -1)
		return (-1);
	address.sin_family = AF_INET;
	address.sin_port = htons(_port);
	address.sin_addr.s_addr = inet_addr(_ip.c_str());
	if (connect(_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
	{
		if (close(_fd) == -1)
			return (-1);
		return (-1);
	}
	return (0);
}

/// Add a data source to a poller's watching list
//  `int pollfd`: The poller's file descriptor
//  `int datafd`: The file descriptor to watch for events
//  `int return`: Zero on success
int gpc::Communication::epollWatch()
{
	struct epoll_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLERR;
	ev.data.fd = _fd;
	if (epoll_ctl(_pollfd, EPOLL_CTL_ADD, _fd, &ev) < 0) {
		close(_fd);
		return (-1);
	}
	return (0);
}

/// Prepare a new poller and add an initial data source to its list
//  `int datafd`: The file descriptor to watch for events
//  `int return`: The poller's file descriptor or -1
int gpc::Communication::epollPrepare()
{
	_pollfd = epoll_create1(0);

	if (_pollfd < 0 || epollWatch() < 0)
		return (-1);
	return 0;
}