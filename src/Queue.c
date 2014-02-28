#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

void enqueue(Queue *queue, QNode *node)
{
	if (queue->length == 0)
	{
		queue->head = node;
		queue->head->next = node; 
		queue->tail = node;
	}
	else {
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->length++;
}

Queue *dequeue(Queue *queue)
{
	return queue;
}