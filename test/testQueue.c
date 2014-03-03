#include <stdlib.h>
#include <stdio.h>
#include "../src/Node.h"
#include "../src/Queue.h"

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
	dequeue(&queue);
	enqueue(&queue, &node);
	enqueue(&queue, &node2);
	enqueue(&queue, &node3);
	printQueue(&queue);
}

void testDequeue()
{
	Queue queue = {.length = 0};
	Node dataNode = {.name="nathan"};
	Node dataNode2 = {.name="mikey"};
	Node dataNode3 = {.name="berko"};

	QNode *data;
	QNode node = {.data=&dataNode};
	QNode node2 = {.data=&dataNode2};	
	QNode node3 = {.data=&dataNode3};	
	enqueue(&queue, &node);
	enqueue(&queue, &node2);
	enqueue(&queue, &node3);
	puts("Dequeue Test");
	printf("head: %s, head->next: %s, tail: %s, length: %d \n ", queue.head->data->name, queue.head->next->data->name, queue.tail->data->name, queue.length);
	data = dequeue(&queue);
	printf("data: %s, length: %d \n ", data->data->name, queue.length);
	data = dequeue(&queue);
	printf("data: %s, length: %d \n ", data->data->name, queue.length);
	data = dequeue(&queue);
	printf("data: %s, length: %d \n ", data->data->name, queue.length);

}

int main()
{
	testEnqueue();
	testDequeue();
}

