#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.h"

#define MAX_NAME_LENGTH 80
#define TYPE_LENGTH 10
#define MAX_NUMBER_CHILDREN 100
#define MAX_PATH_LENGTH 25

Node *new_Node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->name = malloc(sizeof(char)*MAX_NAME_LENGTH);
	node->type = malloc(sizeof(char)*TYPE_LENGTH);
	node->children = malloc(MAX_NUMBER_CHILDREN*sizeof(char*));
	node->path = malloc(MAX_PATH_LENGTH*sizeof(char*));
	node->numberChildren = 0;
	node->pathLength = 0;
	return node;
}

void addChild(Node *parentNode, const char *child)
{
	parentNode->children[parentNode->numberChildren] = malloc(sizeof(char)*MAX_NAME_LENGTH);
	strcpy(parentNode->children[parentNode->numberChildren], child);
	parentNode->numberChildren++;
}

void addToPath(Node *parentNode, const char *child)
{
	parentNode->path[parentNode->pathLength] = malloc(sizeof(char)*MAX_NAME_LENGTH);
	strcpy(parentNode->path[parentNode->pathLength], child);
	parentNode->pathLength++;
}

void buildChildPath(Node *childNode, Node *parentNode)
{
	for (int i=0; i<parentNode->pathLength; i++)
	{
		addToPath(childNode, parentNode->path[i]);
	}
	addToPath(childNode, childNode->name);
}

void free_Node(Node *node)
{
	free(node->type);
	free(node->name);
	free(node->children);
	free(node->path);
	free(node);
}