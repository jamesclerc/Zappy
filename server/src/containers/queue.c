/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Queue Implementation
*/

#include <stdlib.h>
#include <string.h>
#include "containers.h"

/// Create a queue
//  `size_t element_size`: The size of the elements the queue will store
queue_t *queue_create(size_t element_size)
{
	queue_t *queue;

	queue = malloc(sizeof(queue_t));
	if (!queue)
		return (NULL);
	memset(queue, 0, sizeof(queue_t));
	queue->element_size = element_size;
	return (queue);
}

/// Destroy a queue
void queue_destroy(queue_t *queue)
{
	char *memory;

	if (queue == NULL)
		return;
	memory = malloc(queue->element_size);
	if (memory == NULL)
		return;
	while (queue->head)
		queue_pop(queue, memory);
	free(memory);
	free(queue);
}

/// Push an element at a queue's end
void queue_push(queue_t *queue, void *element)
{
	void *transfer;

	if (queue == NULL)
		return;
	transfer = malloc(sizeof(queue->element_size));
	if (transfer == NULL)
		return;
	memcpy(transfer, element, queue->element_size);
	list_insert(&queue->head, transfer);
	if (queue->tail == NULL)
		queue->tail = queue->head;
}

/// Pop an element from a queue's head
void queue_pop(queue_t *queue, void *element)
{
	void *transfer;

	if (queue == NULL)
		return;
	transfer = list_remove(&queue->tail);
	if (queue->tail == NULL)
		queue->head = NULL;
	if (transfer == NULL)
		return;
	if (element != NULL)
		memcpy(element, transfer, queue->element_size);
	free(transfer);
}
