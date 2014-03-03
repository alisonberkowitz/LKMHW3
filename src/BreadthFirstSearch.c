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
	Node startNode = actorNode(startActorName, conn);
	QNode qStartNode = {.data=&startNode};
	Queue frontier = {.length = 0};
	
	Path *currentPath = malloc(sizeof(Path));
	Path *defaultPath = malloc(sizeof(Path));
	currentPath->length=0;
	defaultPath -> length = 0;
	append(currentPath, startActorName);
	startNode.path = currentPath;
	
	map_t visited = hashmap_new();
	enqueue(&frontier, &qStartNode);
	while((frontier.length > 0) && (frontier.length<10))
	{
		Node *currentNode = dequeue(&frontier)->data;

		if (currentNode->name == goalActorName) {
			return currentNode->path;
		}
		for (int i = 0; i<currentNode->numberChildren; i++)
		{
			Node childNode;
			if (strcmp(currentNode->type, "actor") == 0)
			{
				childNode = actorNode(currentNode->children[i], conn);
			}
			else
			{
				childNode = movieNode(currentNode->children[i], conn);
			}
			printf("current node: %s child node: %s\n", currentNode->name, childNode.name);
			QNode qChildNode = {.data=&childNode};
			enqueue(&frontier, &qChildNode);
		}
	}
	
	return defaultPath; // Todo make default
}

int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Path *p;
	p = BFS("Michael Jordan", "Shaq");
	return 0;
}