#include "Path.h"

#ifndef Node_H
#define Node_H

typedef struct
{
  char *type;
  char *name;
  char **children; // For now lets assume that someone will have up to 100 children
  int numberChildren;
} Node;

#endif

Node *new_Node();
void free_Node(Node *node);
void addChild(Node *parentNode, char *child);