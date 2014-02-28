#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"
#include "Queries.h"

int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );

	Node node = movieNode("Shazzam", conn);
	printf("%s\n", node.name);
	printf("%s\n", node.type);
	printf("%d\n", node.numberChildren);
	for (int i=0; i<node.numberChildren; i++)
	{
		printf("%s\n", node.children[i]);
	}
	return 0;
}