/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Method declarations for querying the mongo database by actor name or movie name
*/

#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"

// Methods commented in implemenation file
void actorNode(Node *node, char *name, mongo *conn);
void movieNode(Node *node, char *name, mongo *conn);