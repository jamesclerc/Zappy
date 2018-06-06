/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Doubly-linked List Implementation
*/

#include <stdlib.h>
#include "containers.h"

/// Insert an element into a list
void list_insert(list_t **list, void *element)
{
	list_t *link;

	if (list == NULL || element == NULL)
		return;
	link = malloc(sizeof(list_t));
	if (link == NULL)
		return;
	link->element = element;
	link->prev = NULL;
	link->next = *list;
	if (link->next != NULL)
		link->next->prev = link;
	*list = link;
}

/// Remove an element from a list
void *list_remove(list_t **list)
{
	list_t *link;
	void *element;

	if (list == NULL || *list == NULL)
		return (NULL);
	link = *list;
	*list = link->prev ? link->prev : link->next;
	if (link->next)
		link->next->prev = link->prev;
	if (link->prev)
		link->prev->next = link->next;
	element = link->element;
	free(link);
	return (element);
}
