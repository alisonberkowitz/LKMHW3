#ifndef Path_H
#define Path_H

typedef struct
{
  char **elements;
  int length;
} Path;

#endif

Path *new_Path();

void free_Path();