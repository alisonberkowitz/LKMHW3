#include "Path.h"
#include <stdlib.h>
#include <stdio.h>
void append(Path *path, char* data)
{
	PNode dataNode;
	dataNode.data = data;
	if (path->length == 0)
	{
		PNode *appendNode = malloc(sizeof(PNode));
		appendNode->data = dataNode.data;
		path->head = appendNode;
		path->tail = appendNode;
	}
	else
	{
		PNode *appendNode = malloc(sizeof(PNode));
		appendNode->data = dataNode.data;
		path->tail->next = appendNode;
		path->tail = appendNode;
	}
	path->length++;
}

void printPath(Path *path)
{
	PNode *currentNode = path->head;
	for (int i=0; i<path->length; i++)
	{
		printf("%s ", currentNode->data);
		currentNode = currentNode->next;
	}
	printf("\n");
}