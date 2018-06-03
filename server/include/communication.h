/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Basic I/O wrappers
*/

#pragma once
#include <stdint.h>

int socket_listen(uint16_t port, int backlog);
int epoll_prepare(int datafd);
int epoll_watch(int pollfd, int datafd);
