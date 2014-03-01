#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongo.h"

typedef struct {
  char *type;
  char *name;
  char children[20][80];
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

void parse( mongo *conn ) {
  FILE *in_file = fopen("dummy.txt", "r");
  char line[100];
  char *p;
  char *name;
  char *movie;
  int numberChildren;
  while(fgets(line,100,in_file)) {
    if (is_name(line)){
      p = strtok(line, "\t");
      name = p;
      printf("name: %s\n", name);
      // add it to the db

      p = strtok(NULL, "\t");
      movie = p;
      printf("movie: %s\n", movie );
      // add it as child of name
    }
    else {
      p = strtok(line, "\t");
      movie = p;
      printf("movie: %s\n", movie );
      // add it as a child of name
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