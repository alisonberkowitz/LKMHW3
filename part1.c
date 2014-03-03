#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongo.h"

typedef struct {
  char *type;
  char *name;
  char *children[20];
  char path[20][80];
  int pathLength;
  int numberChildren;
} Node;

int is_name(char *line) {
  if (*line != '\t'){
    return 1;
  }
  else {
    return 0;
  }
}

void set_name(Node *n, char *guy) {
  n->numberChildren = 0;
  n->type = "actor";
  strcpy(n->name, guy);
}

void add_child(Node *n, char *movie) {
  strcpy(n->children[n->numberChildren], movie);
  n->numberChildren = n->numberChildren +1;
}

int totalActors(FILE *in_file) {
  char line[100];
  int count = 0;
  while(fgets(line,100,in_file)) {
    if (is_name(line)){
      count = count + 1;
    }
  }
  return count;
}

void parse( mongo *conn ) {
  FILE *in_file = fopen("dummy.txt", "r");
  char line[100];
  char *p;
  char *guy;
  char *movie;
  int numberChildren;
  int total;

  total = totalActors(in_file);
  printf("totalActors: %i\n", total);
  rewind(in_file);

  Node nodes[total];
  int g = -1;

  while(fgets(line,100,in_file)) {
    if (is_name(line)) {
      g = g+1;
      p = strtok(line, "\t");
      guy = p;
      set_name(&nodes[g], guy);
      printf("name: %s\n", nodes[g].name);

      p = strtok(NULL, "\t");
      movie = p;
      add_child(&nodes[g], movie);
      printf("movie: %s\n", nodes[g].children[0] );
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
  fclose(in_file);
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

  parse( conn );

  mongo_destroy( conn );

  return 0;
}