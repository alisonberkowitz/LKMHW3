/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Methods for the node model we use to represent actors and movies
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Node.h"

#define MAX_NAME_LENGTH 80
#define TYPE_LENGTH 10
#define MAX_NUMBER_CHILDREN 1000
#define MAX_PATH_LENGTH 25

/* Constructor function for a node object which represents a movie or an actor

   returns a malloc'd node
*/
Node *new_Node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (node == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	node->name = (char *)malloc(sizeof(char)*MAX_NAME_LENGTH);
	if (node->name == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	node->type = (char *)malloc(sizeof(char)*TYPE_LENGTH);
	if (node->type == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	node->children = (char **)malloc(MAX_NUMBER_CHILDREN*sizeof(char*));
	if (node->children == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	node->path = (char **)malloc(MAX_PATH_LENGTH*sizeof(char*));
	if (node->path == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	node->numberChildren = 0;
	node->pathLength = 0;
	return node;
}

/* Adds a child to a node and updates the number of children. For 
actors, children are movies
	and for movies children are actors

   *parentNode: node to add a child to
   *child: string for the name of the child you want to add

*/
void addChild(Node *parentNode, const char *child)
{
	parentNode->children[parentNode->numberChildren] = 
		malloc(sizeof(char)*(strlen(child))+1);
	if (parentNode->children[parentNode->numberChildren] == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	strcpy(parentNode->children[parentNode->numberChildren], child);
	parentNode->numberChildren++;
}

/* Adds an element to the path of the current node

   *parentNode: node to add a path element to
   *child: string for the name of the path you want to add

*/
void addToPath(Node *parentNode, const char *child)
{
	parentNode->path[parentNode->pathLength] = 
		malloc(sizeof(char)*(strlen(child)+1));
	if (parentNode->path[parentNode->pathLength] == NULL) {
        fprintf(stderr, "Malloc failed\n");
        exit(1);
    }
	strcpy(parentNode->path[parentNode->pathLength], child);
	parentNode->pathLength++;
}

/* Copies the path of a parent into the path of a child node

   *childNode: destination node for path copying
   *parentNode: node whose path you want to copy

*/
void buildChildPath(Node *childNode, Node *parentNode)
{
	for (int i=0; i<parentNode->pathLength; i++)
	{
		addToPath(childNode, parentNode->path[i]);
	}
	addToPath(childNode, childNode->name);
}


/* Frees memory for the node
	
	*node: node that will be freed
*/
void free_Node(Node *node)
{
	free(node->children);
	free(node->path);
	free(node);
}