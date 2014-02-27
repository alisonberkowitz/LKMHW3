#ifndef Node_H
#define Node_H

typedef struct
{
  const char *type;
  const char *name;
  char children[20][80];
  char path[20][80];
  int pathLength;
  int numberChildren;
} Node;

#endif