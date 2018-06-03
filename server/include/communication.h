/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Basic I/O wrappers
*/

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <sys/epoll.h>
#include "game.h"

#define QUEUE_SIZE 16

int socket_listen(uint16_t port, int backlog);
int epoll_prepare(int datafd);
int epoll_watch(int pollfd, int datafd);
bool event_handle(game_t *, struct epoll_event *, int epoll_fd, int server_fd);
