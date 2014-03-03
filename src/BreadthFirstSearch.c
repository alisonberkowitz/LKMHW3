#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"
#include "Queries.h"
#include "Queue.h"
#include "Hashmap.h"

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
	int error = hashmap_put(map, startNode->name, &x); //Todo add error checking

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
				fprintf(stderr, "%s\n", "Type Error: Node type must be actor or movie");
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
	}
	return startNode;
}

int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Node *p;
	p = BFS("Kevin Bacon", "Shaq");
	for (int i = 0; i < p->pathLength; i++)
		printf("%s\n", p->path[i]);
	return 0;
}