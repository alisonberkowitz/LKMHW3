#include "Node.h"
#ifndef Queue_H
#define Queue_H

typedef struct QNode
{
  Node *data;
  struct QNode *next;
} QNode;

typedef struct
{
  struct QNode *head;
  struct QNode *tail;
  int length;
} Queue;

#endif
void enqueue(Queue *queue, QNode *node);

Queue *dequeue(Queue *queue);