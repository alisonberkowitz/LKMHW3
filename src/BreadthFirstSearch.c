#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"
#include "Queries.h"
#include "Queue.h"
#include "Hashmap.h"
#include "Path.h"

Path *BFS(char *startActorName, char *goalActorName){
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Node *startNode = new_Node();
	actorNode(startNode, startActorName, conn);

	QNode *qStartNode = new_QNode();
	qStartNode->data=startNode;
	Queue *frontier = new_Queue();

	// Hashmap stuff
	map_t map = hashmap_new();
	int x = 1; // Dummy variable for hashmap value
	int y = 0;
	// 
	
	// Ignore Me For Now
	Path *currentPath = malloc(sizeof(Path));
	Path *defaultPath = malloc(sizeof(Path));
	currentPath -> length=0;
	defaultPath -> length = 0;
	// append(currentPath, startActorName);
	// startNode.path = currentPath;
	// This doesnt work
	
	enqueue(frontier, qStartNode);
	int error = hashmap_put(map, startNode->name, &x); //Todo add error checking

	while((frontier->length) > 0)
	{
		Node *currentNode = new_Node();
		QNode *currentQNode = new_QNode();
		dequeue(currentQNode, frontier);
		currentNode = currentQNode->data;
		if (strcmp(currentNode->name, goalActorName) == 0) {
			printf("%s\n", "actor found!");
			return defaultPath;
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
				fprintf(stderr, "%s\n", "Type Error: Node type must be actor or movie");
			}
			QNode *qChildNode = new_QNode();
			qChildNode->data = childNode;
			
			error = hashmap_get(map, childNode->name, (void**)(&y));
			if (error == MAP_MISSING)
			{
				enqueue(frontier, qChildNode);
				error = hashmap_put(map, childNode->name, (void**)(&x));
			}
		}
	}
	return defaultPath; // Todo make default path object
}

int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Path *p;
	p = BFS("Kevin Bacon", "Shaq");
	return 0;
}