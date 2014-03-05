/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Test cases for querying the database by actor or by movie
*/

#include <stdlib.h>
#include <stdio.h>
#include "mongo.h"
#include "../src/Node.h"
#include "../src/Queries.h"

/* Queries the test database for actors and movies and prints out the results from the query
*/
void testQuery()
{
	mongo conn[1];
	int status = mongo_client( conn, "127.0.0.1", 27017 );

	Node *actor_node = new_Node();
	Node *movie_node = new_Node();
	actorNode(actor_node, "Shaq", conn);
	movieNode(movie_node, "Star Wars", conn);
	printf("actor name: %s actor type: %s number children:%d\n", 
		actor_node->name, actor_node->type, actor_node->numberChildren);
	for (int i=0; i<actor_node->numberChildren; i++)
	{
		printf("actor child: %s\n", actor_node->children[i]);
	}
	printf("movie name: %s movie type: %s movie children:%d\n", 
		movie_node->name, movie_node->type, movie_node->numberChildren);
	for (int i=0; i<movie_node->numberChildren; i++)
	{
		printf("movie child: %s\n", movie_node->children[i]);
	}
}

int main()
{
	testQuery();
	return 0;
}
