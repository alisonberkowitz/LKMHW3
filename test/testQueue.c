/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Test cases for Queue implementation
*/

#include <stdlib.h>
#include <stdio.h>
#include "../src/Node.h"
#include "../src/Queue.h"

/* Creates a fake queue, enqueues some fake nodes and prints the queue
*/
void testEnqueue()
{
	Queue queue = {.length = 0};
	Node dataNode = {.name="nathan"};
	Node dataNode2 = {.name="mikey"};
	Node dataNode3 = {.name="allison"};

	QNode node = {.data=&dataNode};
	QNode node2 = {.data=&dataNode2};
	QNode node3 = {.data=&dataNode3};

	enqueue(&queue, &node);
	enqueue(&queue, &node);
	enqueue(&queue, &node2);
	enqueue(&queue, &node3);
	
	puts("Enqueue Test");
	printQueue(&queue);
}

/* Creates a fake queue, enqueues some fake nodes and prints the queue. Then dequeues the nodes and prints
the results of the deqeueue.
*/

void testDequeue()
{
	Queue *queue = new_Queue();
	Node *dataNode = new_Node();
	Node *dataNode2 = new_Node();
	Node *dataNode3 = new_Node();

	dataNode->name = "nathan";
	dataNode2->name = "mikey";
	dataNode3->name = "berko";

	QNode *data = new_QNode();
	QNode *qnode = new_QNode();
	QNode *qnode2 = new_QNode();
	QNode *qnode3 = new_QNode();

	qnode->data = dataNode;
	qnode2->data = dataNode2;
	qnode3->data = dataNode3;

	enqueue(queue, qnode);
	enqueue(queue, qnode2);
	enqueue(queue, qnode3);

	puts("Dequeue Test");
	printf("head: %s, head->next: %s, tail: %s, length: %d \n ", queue->head->data->name, queue->head->next->data->name, queue->tail->data->name, queue->length);
	dequeue(data, queue);
	printf("data: %s, length: %d \n ", data->data->name, queue->length);
	dequeue(data, queue);
	printf("data: %s, length: %d \n ", data->data->name, queue->length);
	dequeue(data, queue);
	printf("data: %s, length: %d \n ", data->data->name, queue->length);

}

int main()
{
	testEnqueue();
	testDequeue();
}

