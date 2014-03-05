#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongo.h"

#define MAX_NUMBER_CHILDREN 500
#define LINE_LENGTH 1000

typedef struct {
  char *name;
  char **children;
  int numberChildren;
} Node;

int is_name(char *line) {
  if ((*line != '\t') && (*line != '\n')){
    return 1;
  }
  else {
    return 0;
  }
}

Node *new_Node(char *guy)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->name = malloc(sizeof(char)*80);
  //node->type = malloc(sizeof(char)*TYPE_LENGTH);
  node->children = malloc(MAX_NUMBER_CHILDREN*sizeof(char*));
  // for (int i = 0; i < MAX_NUMBER_CHILDREN; i++)
  // {
 //     node->children[i] = malloc(80 * sizeof(char));
  // }

  node->numberChildren = 0;
  strcpy(node->name, guy);
  return node;
}

void set_name(Node *n, char *guy) {
  n->children = malloc(MAX_NUMBER_CHILDREN*sizeof(char*));
  n->numberChildren = 0;
  //printf("%s\n", guy);
  n->name = (char*)malloc((strlen(guy)+1)*sizeof(char));
  strcpy(n->name, guy);
}

void add_child(Node *n, char *movie) {
  if (n->numberChildren<=MAX_NUMBER_CHILDREN) {
    n->children[n->numberChildren] = (char*)malloc((strlen(movie)+1)*sizeof(char));
    strcpy(n->children[n->numberChildren], movie);
    // if (n->numberChildren>=MAX_NUMBER_CHILDREN) {
    //   n->children = realloc(n->children, (n->numberChildren)*sizeof(char*));
    // }
    n->numberChildren = n->numberChildren +1;
  }
}

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

void free_Node(Node *node)
{
  //free(node->type);
  // free(node->name);
  free(node->children);
  free(node);
}

void parse( mongo *conn, FILE *in_file ) {
  char line[LINE_LENGTH];
  char *p;
  char *guy;
  char *movie;
  int numberChildren;
  int total;
  bson *a;
  bson **as;

  //total = totalActors(in_file);
  //printf("totalActors: %i\n", total);
  //rewind(in_file);

  Node *node;
  // = (Node*) malloc(sizeof(Node));
  int g = -1;

  while(fgets(line,LINE_LENGTH,in_file)) {
    if (is_name(line)) {
      g = g+1;
      p = strtok(line, "\t");
      guy = p;
      //set_name(node, guy);
      node = new_Node(guy);
      //printf("name: %s\n", nodes[g].name);

      p = strtok(NULL, "\t");
      movie = p;
      add_child(node, movie);
      //printf("movie: %s\n", nodes[g].children[0] );
    }
    else if (*line == '\n')
    {
      free(node->children);
      free(node);
    }
    else {
      p = strtok(line, "\t");
      movie = p;
      add_child(node, movie);
      // printf("name: %s\n, children:", nodes[g].name);
      // int i;
      // for (i=0; i<nodes[g].numberChildren; i++) {
      //   printf("%s\n", nodes[g].children[i]);
      // }
    }
  }
  // int i, j;
  // as = ( bson ** )malloc( sizeof( bson * ) * total);
  // for ( i = 0; i < total; i++ ) {
  //   a = ( bson * )malloc( sizeof( bson ) );
  //   bson_init( a );

  //   bson_append_new_oid( a, "_id" );
  //   bson_append_string( a, "type", "actor" );
  //   bson_append_string( a, "name", nodes[i].name );
  //   bson_append_int( a, "numberChildren", nodes[i].numberChildren );
    
  //   bson_append_start_array(a, "children");
  //   for (j = 0; j<(nodes[i].numberChildren); j++)
  //   {
  //     char str[15];
  //     sprintf(str, "%d", j);
  //     bson_append_string(a,str,nodes[i].children[j]);
  //   }
  //   bson_append_finish_array(a);

  //   bson_finish( a );
  //   as[i] = a;
  // }
  // mongo_insert_batch( conn, "prod.db", (const bson **) as, total, 0, 0 );

  // for ( i = 0; i < total; i++ ) {
  //   bson_destroy( as[i] );
  //   free( as[i] );
  // }
}

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