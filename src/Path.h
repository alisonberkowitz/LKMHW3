#ifndef Path_H
#define Path_H

typedef struct PNode
{
  const char *data;
  struct PNode *next;
} PNode;

typedef struct
{
  struct PNode *head;
  struct PNode *tail;
  int length;
} Path;

#endif

Path *new_Path();

void free_Path();

void append(Path *path, char* data);

void printPath(Path *path);