//circle_queue.c
//Made by Nick M
#include "circle_queue.h"
#include "stdio.h"


circle_queue* circle_queue_init(circle_queue* q){
    q->head = -1;
    q->tail= -1;
    q->cap = CIRCLE_Q_BUFSIZE;
    q->burden = 0;
    q->put = &(circle_queue_put);
    q->get = &(circle_queue_get);
    q->peek = &(circle_queue_peek);
    return q;
}



bool circle_queue_put(circle_queue *q, const Q_data *msg){
    bool success = false;
    // FIRST check if there is room in the queue
    if((q->head == 0) && (q->tail == q->cap-1)) {
        return success;
    }
    else if(q->head == -1)
    {
        q->head = q->tail;
        q->buffer[q->tail] = *msg;
        success = true;
        return success;
    }

    else if((q->tail == q->cap-1) && (q->head != 0))
    {
        q->tail = 0;
        q->buffer[q->tail] = *msg;
        success = true;
        return success;
    }
    else
    {
        q->tail += 1;
        q->buffer[q->tail] = *msg;
        success = true;
        return success;
    }

    return success;
}


bool circle_queue_get(circle_queue *q, Q_data  *msg){
    bool success = false;
    // FIRST check if there is data in the queue
    if (q->head == -1)
    {
        return success;
    }

    *msg = q->buffer[0];
    Q_data test;
    test.int_val = -1;
    q->buffer[q->head] = test;
    if (q->head == q->tail)
    {
        q->head = -1;
        q->tail = -1;
    }
    else if (q->head == q->cap-1) {
        q->head = 0;
    }
    else {
        q->head += 1;
    }
    success = true;
    return success;
}


bool circle_queue_peek(const circle_queue *q, Q_data  *msg){
    bool success = false;
    // FIRST check if there is data in the queue
    if (q->head == -1){
        success = false;
    }
    // If YES - copy data but do not modify anything.
    else {
        *msg = q->buffer[0];
        success = true;
    }
    return success;
}

