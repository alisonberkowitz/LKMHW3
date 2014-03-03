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

QNode *dequeue(Queue *queue)
{
	QNode *data;
	if (queue->length == 0)
	{
		fprintf(stderr, "%s\n", "Error: Dequeing from an empty queue");
	}
	if (queue->length == 1)
	{
		data = queue->head;
		queue->length--;
		return data;
	}

	else {
		data = queue->head;
		queue->head = queue->head->next;
		queue->length--;
		return data;
	}
}

void printQueue(Queue *queue)
{
	QNode *currentNode;
	currentNode = queue->head;
	for (int i=0; i<queue->length; i++)
	{
		printf("%s\n", currentNode->data->name);
		currentNode = currentNode->next;
	}

}