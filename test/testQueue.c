#include <stdlib.h>
#include <stdio.h>
#include "../src/Node.h"
#include "../src/Queue.h"

int main()
{
	Queue queue = {.length = 0};
	Node dataNode = {.name="nathan"};
	Node dataNode2 = {.name="mikey"};
	QNode node = {.data=&dataNode};
	QNode node2 = {.data=&dataNode2};
	enqueue(&queue, &node);
	enqueue(&queue, &node2);
	printf("%s\n", queue.head->data->name);
}