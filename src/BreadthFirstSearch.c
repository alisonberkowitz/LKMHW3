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
	// hashmap_put(visited, startNode.name, &startNode); // Todo add error handling
	// while(frontier.length > 0)
	while((frontier.length > 0) && (frontier.length<10))
	{
		// printQueue(&frontier);
		QNode *currentQNode = dequeue(&frontier);
		Node *currentNode = currentQNode->data;

		if (currentNode->name == goalActorName) {
			return currentNode->path;
		}
		for (int i = 0; i<currentNode->numberChildren; i++)
		{
			Node childNode;
			if (strcmp(currentNode->type, "actor") == 0)
			{
				childNode = movieNode(currentNode->children[i], conn);

			}
			else
			{
				childNode = actorNode(currentNode->children[i], conn);
				
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
	// printPath(p);
	// for (int i =0; i<1; i++)
	// {
	// 	printf("%s\n", path);

	// }


	// printf("%s\n", node.name);
	// printf("%s\n", node.type);
	// printf("%d\n", node.numberChildren);
	// for (int i=0; i<node.numberChildren; i++)
	// {
	// 	printf("%s\n", node.children[i]);
	// }
	return 0;
}