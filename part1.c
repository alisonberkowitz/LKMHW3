/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    This file contains parsing logic and database logic for putting a 
    dataset of actors and movies into a mongo database
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongo.h"

#define MAX_NUMBER_CHILDREN 500
#define LINE_LENGTH 1000

// Struct representing an actor
typedef struct {
  char *name;
  char **children;
  int numberChildren;
} Node;

/*  Checks whether a line contains the name of a new actor
    
    *line: the line to parse

    returns 1 if it has an actor name, 0 if not
*/
int is_name(char *line) {
  if ((*line != '\t') && (*line != '\n')){
    return 1;
  }
  else {
    return 0;
  }
}

/*  Sets the name of a node and allocates memory for its children
    
   *n: node to set the name of
   *guy: name of the actor
*/
void set_name(Node *n, char *guy) {
  n->children = malloc(MAX_NUMBER_CHILDREN*sizeof(char*));
  if (n->children == NULL) {
    fprintf(stderr, "failed to allocate memory to children.\n");
    exit(-1);
  }
  n->numberChildren = 0;
  n->name = (char*)malloc((strlen(guy)+1)*sizeof(char));
  if (n->name == NULL) {
    fprintf(stderr, "failed to allocate memory to name.\n");
    exit(-1);
  }
  strcpy(n->name, guy);
}

/*  Adds a movie child to an actor node and updates the number of children.
    
    *n: parent actor node to add child to
    *movie: name of child to add
*/
void add_child(Node *n, char *movie) {
  if (n->numberChildren<=MAX_NUMBER_CHILDREN) {
    n->children[n->numberChildren] = (char*)malloc((strlen(movie)+1)*sizeof(char));
    if (n->children[n->numberChildren] == NULL) {
      fprintf(stderr, "failed to allocate memory to next child.\n");
      exit(-1);
    }
    strcpy(n->children[n->numberChildren], movie);
    if (n->numberChildren>=MAX_NUMBER_CHILDREN) {
      n->children = realloc(n->children, (n->numberChildren)*sizeof(char*));
      if (n->children == NULL) {
        fprintf(stderr, "failed to reallocate memory to children.\n");
        exit(-1);
      }
    }
    n->numberChildren = n->numberChildren +1;
  }
}

/*  Calculates the total actors in a file

    *in_file: the opened file to parse
    returns count: the total number of actors in that file
*/
int totalActors(FILE *in_file) {
  char line[LINE_LENGTH];
  int count = 0;
  while(fgets(line,LINE_LENGTH,in_file)) {
    if (is_name(line)){
      count = count + 1;
    }
  }
  return count;
}

/*  Parses the data line by line and extracts actor nodes and their movie children
    Adds these actor nodes to the database

    *conn: mongo connection
    *in_file: opened file to parse through
*/
void parse( mongo *conn, FILE *in_file ) {
  char line[LINE_LENGTH];
  char *p;
  char *guy;
  char *movie;
  int numberChildren;
  int total;
  bson *a;
  bson **as;

  total = totalActors(in_file);
  printf("totalActors: %i\n", total);
  rewind(in_file);

  Node *nodes = (Node*) malloc(sizeof(Node)*total);
  if (nodes == NULL) {
    fprintf(stderr, "failed to allocate memory for nodes array.\n");
    exit(-1);
  }
  int g = -1;
  rewind(in_file);

  while(fgets(line,LINE_LENGTH,in_file)) {
    if (is_name(line)) {
      g = g+1;
      p = strtok(line, "\t");
      guy = p;
      set_name(&nodes[g], guy);

      p = strtok(NULL, "\t");
      movie = p;
      add_child(&nodes[g], movie);

    }
    else if (*line == '\n')
    {
      free(&nodes[g]);
    }
    else {
      p = strtok(line, "\t");
      movie = p;
      add_child(&nodes[g], movie);
      printf("name: %s\n, children:", nodes[g].name);
      int i;
      for (i=0; i<nodes[g].numberChildren; i++) {
        printf("%s\n", nodes[g].children[i]);
      }
    }
  }
  int i, j;
  as = ( bson ** )malloc( sizeof( bson * ) * total);
  if (as == NULL) {
    fprintf(stderr, "failed to allocate memory for bson array.\n");
    exit(-1);
  }
  for ( i = 0; i < total; i++ ) {
    a = ( bson * )malloc( sizeof( bson ) );
    if (a == NULL) {
      fprintf(stderr, "failed to allocate memory for bson object.\n");
      exit(-1);
    }
    bson_init( a );

    bson_append_new_oid( a, "_id" );
    bson_append_string( a, "type", "actor" );
    bson_append_string( a, "name", nodes[i].name );
    bson_append_int( a, "numberChildren", nodes[i].numberChildren );
    
    bson_append_start_array(a, "children");
    for (j = 0; j<(nodes[i].numberChildren); j++)
    {
      char str[15];
      sprintf(str, "%d", j);
      bson_append_string(a,str,nodes[i].children[j]);
    }
    bson_append_finish_array(a);

    bson_finish( a );
    as[i] = a;
  }
  mongo_insert_batch( conn, "prod.db", (const bson **) as, total, 0, 0 );

  for ( i = 0; i < total; i++ ) {
    bson_destroy( as[i] );
    free( as[i] );
  }
}

/* Useful debugging feature to print all nodes in a given collection
    *conn: a connection to the mongo database
*/
static void display_graph( mongo *conn) {
  mongo_cursor cursor[1];
  mongo_cursor_init( cursor, conn, "prod.db" );

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

  mongo_cmd_drop_collection( conn, "prod", "db", NULL); 

  FILE *in_file = fopen("actors.list", "r");
  parse( conn, in_file );
  fclose(in_file);

  display_graph( conn );
  mongo_destroy( conn );

  return 0;
}