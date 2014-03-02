#ifndef Node_H
#define Node_H

typedef struct
{
  const char *type;
  const char *name;
  const char *children[20];
  const char *path[20];
  int pathLength;
  int numberChildren;
} Node;

#endif