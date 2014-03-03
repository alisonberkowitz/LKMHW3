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

void append(Path *path, char* data);
void printPath(Path *path);