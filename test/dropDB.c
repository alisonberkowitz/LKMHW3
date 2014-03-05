/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Drops all records from the test nodes collection
*/

#include <stdio.h>
#include <stdlib.h>
#include "mongo.h"

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
  mongo_cmd_drop_collection( conn, "test", "seeddb", NULL); 
  mongo_destroy( conn );

  return 0;
}