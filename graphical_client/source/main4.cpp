/*
** EPITECH PROJECT, 2018
** main4.cpp
** File description:
** main4
*/

#include "GraphicClient.hpp"

int main()
{
	sf::RenderWindow *window = new sf::RenderWindow;
	gpc::GraphicClient client(window, new gpc::Menu(*window));
	return(1);
}