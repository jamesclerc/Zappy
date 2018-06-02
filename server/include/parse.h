/*
** EPITECH PROJECT, 2018
** parse.h
** File description:
** header
*/

#pragma once
#include "team.h"

team_t *parse_arguments(int ac, char **av, int *args);
void print_usage(char *av0, int exit_value);
