/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Queue implementation with linked lists
*/

#pragma once

typedef struct list_link_s list_link_t;
typedef struct queue_s queue_t;

struct list_link_t
{
	void *element;
	list_link_t *prev;
	list_link_t *next;
};

struct queue_s
{
	size_t element_size;
	list_link_t *head;
	list_link_t *tail;
};

queue_t *queue_create(size_t);
void queue_destroy(queue_t *);
void queue_push(queue_t *, void *);
void queue_pop(queue_t *, void *);
