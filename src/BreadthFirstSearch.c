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
	
	enqueue(frontier, qStartNode);

	while(frontier->length > 0)
	{
		Node *currentNode = new_Node();
		currentNode = dequeue(frontier)->data;

		if (currentNode->name == goalActorName) {
			return defaultPath;
		}
		// printf("%d\n", currentNode->numberChildren);
		// printf("%s\n", currentNode->name);
		for (int i = 0; i<currentNode->numberChildren; i++)
		{
			Node *childNode = new_Node();
			if (strcmp(currentNode->type, "actor") == 0)
			{
				actorNode(childNode, currentNode->children[i], conn);
			}
			else
			{
				movieNode(childNode, currentNode->children[i], conn);
			}
			printf("current node: %s child node: %s\n", currentNode->name, childNode->name);
			QNode *qChildNode = new_QNode();
			qChildNode -> data = childNode;
			enqueue(frontier, qChildNode);
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