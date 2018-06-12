/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Data Structures
*/

#pragma once
#include <stddef.h>

typedef struct list_s list_t;
typedef struct queue_s queue_t;

struct list_s
{
	void *element;
	list_t *prev;
	list_t *next;
};

struct queue_s
{
	size_t element_size;
	list_t *head;
	list_t *tail;
};

void list_insert(list_t **, void *);
void *list_remove(list_t **);

queue_t *queue_create(size_t);
void queue_destroy(queue_t *);
void queue_push(queue_t *, void *);
void queue_pop(queue_t *, void *);
