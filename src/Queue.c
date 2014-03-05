/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Methods for the queue datastructure we use for breadth first traversal
*/

#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"
#include <string.h>

/* Enqueues a node onto the tail of the queue

   *queue: Queue struct you want to put the node into 
   *node: QNode you want to enqueue
*/
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

/* Dequeues a node onto the tail of the queue

   *data: QNode you want to put the dequeued data into 
   *queue: Queue struct you want to dequeue the node from
*/
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

/* Constructor function for a QNode 
	QNodes wrap Nodes so they can be put into a Queue

   returns a malloc'd QNode
*/
QNode *new_QNode()
{
	QNode *qNode = malloc(sizeof(QNode));
	if (qNode == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	qNode->data = malloc(sizeof(Node));
	if (qNode->data == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
  	qNode->next = malloc(sizeof(QNode));
	if (qNode->next == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
  	return qNode;
}

/* Frees memory for the QNode
	
	*qNode: QNode that will be freed
*/
void free_QNode(QNode *qNode)
{
	free(qNode);
}

/* Constructor function for a Queue 

   returns a malloc'd Queue
*/
Queue *new_Queue()
{
	Queue *queue = malloc(sizeof(Queue));
	if (queue == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	queue->length = 0;
	queue->head = malloc(sizeof(QNode));
	if (queue->head == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	queue->tail = malloc(sizeof(QNode));
	if (queue->tail == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	return queue;
}

/* Frees memory for the Queue
	
	*queue: queue that will be freed
*/
void free_Queue(Queue *queue)
{
	free(queue->head);
	free(queue->tail);
	free(queue);
}

/* Useful debuggin function for printing all elements within a queue

   *queue: queue whose contents will be printed
*/
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