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

  if( bson_init( query ) != BSON_OK )
      printf(" Error initing query. ");

  if( bson_append_string( query, "name", name ) != BSON_OK )
      printf(" Error appending string to query. ");

  if( bson_finish( query ) != BSON_OK )
      printf(" Error finishing query. ");

  mongo_cursor_init( cursor, conn, "test.seeddb" ); // No error returned from this method
  mongo_cursor_set_query( cursor, query ); // No error returned from this method
  
  int i=0;
  node->type = "actor";
  node->name = name;
  //  Iterate through the mongo collection and find all children. Add children and 
  // update child count as children are found
  while( mongo_cursor_next( cursor ) == MONGO_OK ) {
  	bson_iterator iterator[1];
  	if ( bson_find( iterator, mongo_cursor_bson( cursor ), "children" )) { // No error returned from this method
  		bson_iterator sub[1];
  		bson_iterator_subiterator(iterator, sub); // No error returned from this method
  		while(bson_iterator_more(sub))
    	{
      	if (bson_iterator_next(sub) != BSON_EOO)
      	{
            addChild(node, bson_iterator_string(sub));
      	}
    	}
  	}
  } 
  bson_destroy( query ); // No error returned from this method
  mongo_cursor_destroy( cursor ); // No error returned from this method
}

/* Searches for an movie by name and puts the data in a node

   *node: node to put the movie data into 
   *conn: mongo connection

*/
void movieNode(Node *node, char *name, mongo *conn)
{
	  bson query[1];
    mongo_cursor cursor[1];

  	if (bson_init( query ) != BSON_OK)
      printf(" Error initing query. ");

  	if (bson_append_start_object(query, "children") != BSON_OK)
      printf("%s\n", "Error appending start object to query");

  	if (bson_append_start_array(query, "$in") != BSON_OK)
      printf("%s\n", "Error appending data to the start of the array");

  	if (bson_append_string( query, "name", name ) != BSON_OK)
      printf("%s\n", " Error appending string to query. ");

  	if (bson_append_finish_array(query) != BSON_OK)
      printf("%s\n", "Error finishing the bson array");

  	if (bson_append_finish_object(query) != BSON_OK)
      printf("%s\n", "Error appending start object to query");

  	if (bson_finish( query ) != BSON_OK)
      printf("%s\n", "Error finishing query");

  	mongo_cursor_init( cursor, conn, "test.seeddb" ); // No error returned from this method
  	mongo_cursor_set_query( cursor, query ); // No error returned from this method

  	int i = 0;
  	node->type = "movie";
  	node->name = name;
  	while( mongo_cursor_next( cursor ) == MONGO_OK ) { // No error returned from this method
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