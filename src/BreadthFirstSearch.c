#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "BreadthFirstSearch.h"
#include "mongo.h"

Node actorNode(char *name, mongo *conn)
{
	bson query[1];
  	mongo_cursor cursor[1];

  	bson_init( query );
  	bson_append_string( query, "name", name );
  	bson_finish( query );

  	mongo_cursor_init( cursor, conn, "test.seeddb" );
  	mongo_cursor_set_query( cursor, query );
  	Node node;
  	int i=0;
  	node.type = "actor";
  	node.name = name;
  	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
    	bson_iterator iterator[1];
    	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "numberChildren" )) {
        	node.numberChildren = bson_iterator_int( iterator );
    	}
    	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "children" )) {
    		bson_iterator sub[1];
    		bson_iterator_subiterator(iterator, sub);
    		while(bson_iterator_more(sub))
		  	{
		    	if (bson_iterator_next(sub) != BSON_EOO)
		    	{
		      		node.children[i] = bson_iterator_string(sub);
		      		i++;
		    	}
		  	}
    	}
  	}
  	bson_destroy( query );
  	mongo_cursor_destroy( cursor );

	return node;
}

Node movieNode(char *name, mongo *conn)
{
	bson query[1];
  	mongo_cursor cursor[1];

  	bson_init( query );
  	bson_append_start_object(query, "children");
  	bson_append_start_array(query, "$in");
  	bson_append_string( query, "name", name );
  	bson_append_finish_array(query);
  	bson_append_finish_object(query);
  	bson_finish( query );

  	mongo_cursor_init( cursor, conn, "test.seeddb" );
  	mongo_cursor_set_query( cursor, query );

  	int i = 0;
  	Node node;
  	node.type = "movie";
  	node.name = name;
  	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
    	bson_iterator iterator[1];
    	bson_iterator subiterator[1];
    	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "name" )) {
    		if ( bson_find( subiterator, mongo_cursor_bson( cursor ), "name" )) {
    			node.children[i] = bson_iterator_string( subiterator );
    			node.numberChildren++;
    			i++;
    		}
    	}    	    	
  	}
  	bson_destroy( query );
  	mongo_cursor_destroy( cursor );
	return node;
}


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