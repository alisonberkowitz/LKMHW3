/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Methods for querying the mongo database by actor name or movie name
*/

#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"

/* Searches for an actor by name and puts the data in a node

   *node: node to put the actor data into 
   *conn: mongo connection

*/
void actorNode(Node *node, char *name, mongo *conn)
{
  bson query[1];
  mongo_cursor cursor[1];

  bson_init( query );
  bson_append_string( query, "name", name );
  bson_finish( query );

  mongo_cursor_init( cursor, conn, "test.seeddb" );
  mongo_cursor_set_query( cursor, query );
  
  int i=0;
  node->type = "actor";
  node->name = name;
  while( mongo_cursor_next( cursor ) == MONGO_OK ) {
  	bson_iterator iterator[1];
  	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "children" )) {
  		bson_iterator sub[1];
  		bson_iterator_subiterator(iterator, sub);
  		while(bson_iterator_more(sub))
    	{
      	if (bson_iterator_next(sub) != BSON_EOO)
      	{
            addChild(node, bson_iterator_string(sub));
      	}
    	}
  	}
  }
  bson_destroy( query );
  mongo_cursor_destroy( cursor );
}

/* Searches for an movie by name and puts the data in a node

   *node: node to put the movie data into 
   *conn: mongo connection

*/
void movieNode(Node *node, char *name, mongo *conn)
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
  	node->type = "movie";
  	node->name = name;
  	while( mongo_cursor_next( cursor ) == MONGO_OK ) {
    	bson_iterator iterator[1];
    	bson_iterator subiterator[1];
    	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "name" )) {
    		if ( bson_find( subiterator, mongo_cursor_bson( cursor ), "name" )) {
          addChild(node, bson_iterator_string(subiterator));
    		}
    	}
  	}
  	bson_destroy( query );
  	mongo_cursor_destroy( cursor );
}