/*
** EPITECH PROJECT, 2018
** GraphicClient.cpp
** File description:
** GraphicClient
*/

#include "GraphicClient.hpp"

GraphicClient &gpc::GraphicClient::instance;

gpc::GraphicClient::GraphicClient()
{
	_menu = Menu(window);
}

GraphicClient &gpc::GraphicClient::getIntance()
{
	return instance;
}

void gpc::GraphicClient::initConnection()
{
	_com.setIp(_menu.getIp());
	_com.setPort(_menu.getPort());
	_com.firstConnection();
}

void gpc::GraphicClient::run()
{
	runmenu();
	initConnection();
	mainLoop();
}

void gpc::GraphicClient::runMenu()
{
	bool test = false;
	while (test == false)
	{
		test = _menu.draw();
	}
}

void gpc::GraphicClient::mainLoop()
{
	while(1)
	{
		_com.mainLoop();
		_map.draw();
		//drawPlayer(); Je sais pas si on va passer par ça
	}
}
gpc::GraphicClient::~GraphicClient()
{
}
