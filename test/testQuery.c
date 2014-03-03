#include <stdlib.h>
#include <stdio.h>
#include "mongo.h"
#include "../src/Node.h"
#include "../src/Queries.h"

void testQuery()
{
	Node *actorNode;
	actorNode = actorNode(actorNode, "Shaq");
	Node *movieNode = movieNode(movieNode, "Star Wars");
	printf("actor name: %s actor type: %s number children:%d\n", actorNode->name, actorNode->type, actorNode->numberChildren);
	for (int i=0; i<actorNode->numberChildren; i++)
	{
		printf("actor child: %s\n", actorNode->children[i]);
	}
	printf("movie name: %s movie type: %s movie children:%d\n", movieNode->name, movieNode->type, movieNode->numberChildren);
	for (int i=0; i<movieNode->numberChildren; i++)
	{
		printf("movie child: %s\n", movieNode->children[i]);
	}
}

int main()
{
	testQuery();
	return 0;
}
