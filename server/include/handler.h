/*
** EPITECH PROJECT, 2018
** handler.h
** File description:
** command handlers header
*/

#pragma once

typedef struct handler_s {
	char *name;
	int duration;
	void (*handle)(char *args, void **data);
	void (*respond)(void *data);
} handler_t;

typedef struct command_s {
	time_t start_time;
	handler_t *cmd;
	void *data;
} command_t;
