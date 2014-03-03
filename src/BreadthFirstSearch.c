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
	
	// Ignore Me For Now
	Path *currentPath = malloc(sizeof(Path));
	Path *defaultPath = malloc(sizeof(Path));
	currentPath -> length=0;
	defaultPath -> length = 0;
	// append(currentPath, startActorName);
	// startNode.path = currentPath;
	// This doesnt work
	
	// enqueue(frontier, qStartNode);
	int frontierLength = 0;
	Node *frontierLst[20];
	frontierLst[frontierLength] = startNode;
	frontierLength++;
	// while(frontier->length > 0)
	while(frontierLength > 0 && frontierLength<20)
	{
		printQueue(frontier);
		Node *currentNode = new_Node();
		QNode *currentQNode = new_QNode();
		// dequeue(currentQNode, frontier);
		currentNode = frontierLst[--frontierLength];
		// currentNode = currentQNode->data;
		// printf("%s %s %d\n", currentNode->type, currentNode->name, currentNode->numberChildren);
		if (currentNode->name == goalActorName) {
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
				printf("%s\n", "error");
			}
			QNode *qChildNode = new_QNode();
			qChildNode->data = childNode;
			frontierLst[frontierLength++] = childNode; 
			// enqueue(frontier, qChildNode);
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