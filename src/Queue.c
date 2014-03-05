#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"
#include <string.h>

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

void dequeue(QNode *data, Queue *queue)
{
	if (queue->length == 0)
	{
		fprintf(stderr, "%s\n", "Error: Dequeing from an empty queue");
	}

	else {
		memcpy(data, queue->head, sizeof(QNode));
		queue->head = queue->head->next;
		queue->length--;
	}
}

QNode *new_QNode()
{
	QNode *qNode = malloc(sizeof(QNode));
	qNode->data = malloc(sizeof(Node));
  	qNode->next = malloc(sizeof(QNode));
  	return qNode;
}

void free_QNode(QNode *qNode)
{
	free(qNode);
}

Queue *new_Queue()
{
	Queue *queue = malloc(sizeof(Queue));
	queue->length = 0;
	queue->head = malloc(sizeof(QNode));
	queue->tail = malloc(sizeof(QNode));
	return queue;
}

void free_Queue(Queue *queue)
{
	free(queue->head);
	free(queue->tail);
	free(queue);
}

void printQueue(Queue *queue)
{
	QNode *currentNode;
	currentNode = queue->head;
	for (int i=0; i<queue->length-1; i++)
	{
		printf("%s\n", currentNode->data->name);
		currentNode = currentNode->next;
	}

}