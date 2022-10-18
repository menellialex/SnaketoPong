//made my nickm
#ifndef CIRCLE_QUEUE_H
#define CIRCLE_QUEUE_H

#include <stdbool.h>
#include <pressed.h>
#include <stdio.h>
#include "pong_enums.h"

#define CIRCLE_Q_BUFSIZE 10

typedef struct circle_queue_struct {
    // ATTRIBUTES
    uint8_t size;
    //JPL violation. We need negative numbers for the tail and the head.
    int tail;
    int head;
    enum pressed buffer[CIRCLE_Q_BUFSIZE];

    // METHODS
    //must be able to put things into a queue using a function
    bool (*put)(struct circle_queue_struct *q, const enum pressed *msg);
    //bool (*peek)(const struct circle_queue_struct *q, enum pressed *msg);
    //must be able get a message out of the struct.
    bool (*get)(struct circle_queue_struct *q,  enum pressed *msg);
    //bool (*display)(struct circle_queue_struct *q);
} circle_queue;

circle_queue* circle_queue_init( circle_queue* Q);
bool circle_queue_put(circle_queue *q, const enum pressed *msg);
//bool circle_queue_peek(const circle_queue *q, enum pressed *msg);
bool circle_queue_get(circle_queue *q, enum pressed *msg);
bool circle_queue_display(struct circle_queue_struct *q);
#endif // CIRCLE_QUEUE_H
