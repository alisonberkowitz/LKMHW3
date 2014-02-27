#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "BreadthFirstSearch.h"
#include "mongo.h"

Node getNodeByName(char *name, mongo *conn)
{
	bson query[1];
  	mongo_cursor cursor[1];

  	bson_init( query );
  	bson_append_string( query, "name", name );
  	bson_finish( query );

  	mongo_cursor_init( cursor, conn, "test.seeddb" );
  	mongo_cursor_set_query( cursor, query );
  	Node node;
  	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
    	bson_iterator iterator[1];
    	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "name" )) {
    		node.name = bson_iterator_string( iterator );
    	}
    	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "type" )) {
        	node.type = bson_iterator_string( iterator );
    	}
  	}

  	bson_destroy( query );
  	mongo_cursor_destroy( cursor );

	return node;
}

static void display_graph( mongo *conn) {
  mongo_cursor cursor[1];
  mongo_cursor_init( cursor, conn, "test.seeddb" );

  while( mongo_cursor_next( cursor ) == MONGO_OK )
    bson_print( &cursor->current );

  mongo_cursor_destroy( cursor );
}


int main()
{
	mongo conn[1]; // TODO add error checking
	int status = mongo_client( conn, "127.0.0.1", 27017 );

	char name[] = "Michael Jordan";
	Node node = getNodeByName(name, conn);
	printf("%s\n", node.name);
	printf("%s\n", node.type);
	return 0;
}