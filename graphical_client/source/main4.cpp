/*
** EPITECH PROJECT, 2018
** main4.cpp
** File description:
** main4
*/

#include "GraphicClient.hpp"
#include "Communication.hpp"

int main()
{
	gpc::GraphicClient::getInstance()->run();
	return(1);
}