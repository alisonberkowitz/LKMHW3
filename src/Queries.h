#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include "mongo.h"

Node actorNode(char *name, mongo *conn);
Node movieNode(char *name, mongo *conn);