/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Breadth First Search Traversal for actor-movie connections
*/

#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"
#include "Queries.h"
#include "Queue.h"
#include "Hashmap.h"

/* Runs a breadth first search for actor-movie paths between any two actors 
	in our database

   startActorName: string for the starting actor in the path
   goalActorName: string for the last actor in the path

   returns a node whose path is the shortest path between the start and 
   ending actor
*/
Node *BFS(char *startActorName, char *goalActorName){
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Node *startNode = new_Node();
	actorNode(startNode, startActorName, conn);
	addToPath(startNode, startNode->name);

	QNode *qStartNode = new_QNode();
	qStartNode->data=startNode;
	Queue *frontier = new_Queue();

	// Hashmap stuff
	map_t map = hashmap_new();
	int x = 1; // Dummy variable for hashmap value
	int y = 0;
	// 
		
	enqueue(frontier, qStartNode);
	int error = hashmap_put(map, startNode->name, &x);

	while((frontier->length) > 0)
	{
		Node *currentNode = new_Node();
		QNode *currentQNode = new_QNode();
		dequeue(currentQNode, frontier);
		currentNode = currentQNode->data;
		if (strcmp(currentNode->name, goalActorName) == 0) {
			return currentNode;
		}
		for (int i = 0; i<currentNode->numberChildren; i++)
		{
			Node *childNode = new_Node();
			if (strcmp(currentNode->type, "actor") == 0)
			{
				movieNode(childNode, currentNode->children[i], conn);
			}
			else if (strcmp(currentNode->type, "movie") == 0)
			{
				actorNode(childNode, currentNode->children[i], conn);
			}
			else {
				fprintf(stderr, 
					"%s\n", "Type Error: Node type must be actor or movie");
			}

			buildChildPath(childNode, currentNode);
			QNode *qChildNode = new_QNode();
			qChildNode->data = childNode;
			
			error = hashmap_get(map, childNode->name, (void**)(&y));
			if (error == MAP_MISSING)
			{
				enqueue(frontier, qChildNode);
				error = hashmap_put(map, childNode->name, (void**)(&x));
			}
		}
		// printf("%s\n", currentNode->name);
		free_Node(currentNode);
		free_QNode(currentQNode);
	}
	return startNode;
}

/* Runs a breadth first search for actor-movie paths between Kevin Bacon and 
Daniel Day lewis for the test data in test/seedDB

   prints the path between these actors
*/
int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Node *p;
	p = BFS("Kevin Bacon", "Daniel Day Lewis");
	for (int i = 0; i < p->pathLength; i++)
		printf("%s\n", p->path[i]);
	return 0;
}