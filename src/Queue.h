/*
    Copyright 2013 Nathan Lintz and Alison Berkowitz
    Method and struct declaration for the queue datastructure we use for breadth first traversal
*/

#include "Node.h"
#ifndef Queue_H
#define Queue_H

/* Node wrapper so nodes can be enqueued and dequeued
*/
typedef struct QNode
{
  Node *data;
  struct QNode *next;
} QNode;

/* FIFO Queue struct for use in Breadth First Search
*/
typedef struct
{
  struct QNode *head;
  struct QNode *tail;
  int length;
} Queue;

#endif

// Methods commented in implementation file
QNode *new_QNode();

Queue *new_Queue();

void free_QNode(QNode *qNode);

void enqueue(Queue *queue, QNode *node);

void dequeue(QNode *data, Queue *queue);

void printQueue(Queue *queue);
