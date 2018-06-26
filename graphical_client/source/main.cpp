/*
** EPITECH PROJECT, 2018
** main4.cpp
** File description:
** main4
*/

#include "GraphicClient.hpp"

int main()
{
	std::cout << sizeof(gpc::Menu) << std::endl;
	gpc::GraphicClient client;
	client.run();
	return(1);
}