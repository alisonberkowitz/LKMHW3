/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Method and struct declarations for the node model we use to 
    represent actors and movies
*/

#ifndef Node_H
#define Node_H

/* Struct representing a movie or an actor
*/
typedef struct
{
  char *type;
  char *name;
  char **children;
  char **path;
  int numberChildren;
  int pathLength;
} Node;

#endif

// Methods commented in implemenation file
Node *new_Node();
void free_Node(Node *node);
void addChild(Node *parentNode, const char *child);
void addToPath(Node *parentNode, const char *child);
void buildChildPath(Node *childNode, Node *parentNode);