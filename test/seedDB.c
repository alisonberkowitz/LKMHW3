/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Creates dummy test data for the BFS and puts it into the mongo database
*/

#include <stdio.h>
#include <stdlib.h>
#include "mongo.h"

/* Struct representing a movie or an actor
*/
typedef struct {
  char *type;
  char *name;
  char children[20][80];
  char path[20][80];
  int pathLength;
  int numberChildren;
} Node;

/* Generates test nodes and puts them into the database

    *conn: a connection to the mongo database
*/
static void generate_test_data( mongo *conn ) {
  bson *p;
  bson **ps;
  int i, j;
  int n=6;

  Node nodes[6] = {
    {.type="actor", .name="Kevin Bacon", .children={"Star Wars", "Space Jam"}, .path={""}, 0, 2},
    {.type="actor", .name="Michael Jordan", .children={"Shazzam", "Space Jam"}, .path={""}, 0, 2},
    {.type="actor", .name="Bugs Bunny", .children={"Shazzam", "Space Jam"}, .path={""}, 0, 2},
    {.type="actor", .name="Shaq", .children={"Shazzam", "Star Wars", "Juno"}, .path={""}, 0, 3},
    {.type="actor", .name="Ellen Page", .children={"Juno", "Lincoln"}, .path={""}, 0, 2},
    {.type="actor", .name="Daniel Day Lewis", .children={"Lincoln"}, .path={""}, 0, 1},
  };

  ps = ( bson ** )malloc( sizeof( bson * ) * n);
  for ( i = 0; i < n; i++ ) {
    p = ( bson * )malloc( sizeof( bson ) );
    bson_init( p );

    bson_append_new_oid( p, "_id" );
    bson_append_string( p, "type", nodes[i].type );
    bson_append_string( p, "name", nodes[i].name );
    bson_append_int( p, "numberChildren", nodes[i].numberChildren );
    
    bson_append_start_array(p, "children");
    for (j = 0; j<(nodes[i].numberChildren); j++)
    {
      char str[15];
      sprintf(str, "%d", j);
      bson_append_string(p,str,nodes[i].children[j]);
    }
    bson_append_finish_array(p);

    bson_finish( p );
    ps[i] = p;
  }

  mongo_insert_batch( conn, "test.seeddb", (const bson **) ps, n, 0, 0 );

  for ( i = 0; i < n; i++ ) {
    bson_destroy( ps[i] );
    free( ps[i] );
  }
}

/* Useful debugging feature to print all nodes in a given collection
    *conn: a connection to the mongo database
*/
static void display_graph( mongo *conn) {
  mongo_cursor cursor[1];
  mongo_cursor_init( cursor, conn, "test.seeddb" );

  while( mongo_cursor_next( cursor ) == MONGO_OK )
    bson_print( &cursor->current );

  mongo_cursor_destroy( cursor );
}

int main() {
  mongo conn[1];
  int status = mongo_client( conn, "127.0.0.1", 27017 );

  if( status != MONGO_OK ) {
      switch ( conn->err ) {
        case MONGO_CONN_NO_SOCKET:  printf( "no socket\n" ); return 1;
        case MONGO_CONN_FAIL:       printf( "connection failed\n" ); return 1;
        case MONGO_CONN_NOT_MASTER: printf( "not master\n" ); return 1;
      }
  }
 
  generate_test_data(conn);
  display_graph(conn);
  mongo_destroy( conn );

  return 0;
}