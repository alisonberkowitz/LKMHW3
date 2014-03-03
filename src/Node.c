#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.h"

#define MAX_NAME_LENGTH 80
#define TYPE_LENGTH 10
#define MAX_NUMBER_CHILDREN 100

Node *new_Node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->name = malloc(sizeof(char)*80);
	node->type = malloc(sizeof(char)*TYPE_LENGTH);
	node->children = malloc(MAX_NUMBER_CHILDREN*sizeof(char*));
	// for (int i = 0; i < MAX_NUMBER_CHILDREN; i++)
	// {
 //    	node->children[i] = malloc(80 * sizeof(char));
	// }

	node->numberChildren = 0;
	return node;
}

void addChild(Node *parentNode, const char *child)
{
	parentNode->children[parentNode->numberChildren] = malloc(sizeof(char)*80);
	strcpy(parentNode->children[parentNode->numberChildren], child);
	parentNode->numberChildren++;
}

void free_Node(Node *node)
{
	free(node->type);
	free(node->name);
	free(node->children);
	free(node);
}