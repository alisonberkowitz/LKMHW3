#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"
#include "Queries.h"
#include "Queue.h"
#include "Hashmap.h"

void BFS(char *path[], char *startActorName, char *goalActorName){
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	Node startNode = movieNode(startActorName, conn);
	QNode qStartNode = {.data=&startNode};
	Queue frontier = {.length = 0};	
	map_t visited = hashmap_new();

	startNode.path[0] = startNode.name;
	enqueue(&frontier, &qStartNode);
	hashmap_put(visited, startNode.name, &startNode); // Todo add error handling
	
	while(frontier.length > 0)
	{
		QNode *currentQNode = dequeue(&frontier);
		Node *currentNode = currentQNode->data;

		if (currentNode->name == goalActorName) {
			// return currentNode->path;
			path = currentNode->path;
		}
	}
	// int error = hashmap_get(visited, startNode.name, (void**)(&startNode));
	// if (error==MAP_OK)
	// {
	// 	printf("%s\n", "Key Found");
	// }


	// return "Nathan";
}

int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );
	char *path[20];
	BFS(path, "Nathan", "Kevin Bacon");
	for (int i =0; i<1; i++)
	{
		printf("%s\n", path);

	}


	// printf("%s\n", node.name);
	// printf("%s\n", node.type);
	// printf("%d\n", node.numberChildren);
	// for (int i=0; i<node.numberChildren; i++)
	// {
	// 	printf("%s\n", node.children[i]);
	// }
	return 0;
}