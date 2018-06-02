/*
** EPITECH PROJECT, 2018
** command.h
** File description:
** command handlers header
*/

#pragma once

typedef struct command_s {
	char *name;
	int duration;
	void (*handle)(void **data);
	void (*respond)(void *data);
} command_t;

typedef struct action_s {
	time_t start_time;
	command_t *cmd;
	void *data;
} action_t;
