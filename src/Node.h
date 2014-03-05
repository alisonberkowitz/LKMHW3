#ifndef Node_H
#define Node_H

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

Node *new_Node();
void free_Node(Node *node);
void addChild(Node *parentNode, const char *child);
void addToPath(Node *parentNode, const char *child);
void buildChildPath(Node *childNode, Node *parentNode);