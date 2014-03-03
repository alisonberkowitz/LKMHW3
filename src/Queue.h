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

QNode *new_QNode();

Queue *new_Queue();

void enqueue(Queue *queue, QNode *node);

void dequeue(QNode *data, Queue *queue);

void printQueue(Queue *queue);
