/*
** EPITECH PROJECT, 2018
** loop.h
** File description:
** header
*/

#pragma once

bool loop(map_t *map, team_t *teams, int epoll_fd, int server_fd);
bool init_loop(map_t *map, team_t *teams, int *args);
