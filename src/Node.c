#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

#define MAX_NAME_LENGTH 80
#define TYPE_LENGTH 6
#define MAX_NUMBER_CHILDREN 100

Node *new_Node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->name = malloc(sizeof(char));
	node->type = malloc(sizeof(char)*TYPE_LENGTH);
	node->children = (char**) malloc(MAX_NUMBER_CHILDREN+1*sizeof(char*));
	node->numberChildren = 0;
	return node;
}

void addChild(Node *parentNode, char *child)
{
	parentNode->children[parentNode->numberChildren] = child;
	parentNode->numberChildren++;
}

void free_Node(Node *node)
{
	free(node->type);
	free(node->name);
	free(node->children);
	free(node);
}