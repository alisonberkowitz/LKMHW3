#include "Path.h"

#ifndef Node_H
#define Node_H

typedef struct
{
  const char *type;
  const char *name;
  const char *children[20];
  Path *path;
  int pathLength;
  int numberChildren;
} Node;

#endif