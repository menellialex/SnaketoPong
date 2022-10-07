//circle_queue.c
//Made by Nick M
#include <circle_queue.h>

circle_queue* circle_queue_init(circle_queue *q) {
    q->head = -1;
    q->tail = -1;
    q->size = CIRCLE_Q_BUFSIZE;
    q->put = &(circle_queue_put);
    q->get = &(circle_queue_get);
    //q->peek = &(circle_queue_peek);
    q->display = &(circle_queue_display);
    return q;
}

bool circle_queue_put(circle_queue *q, const enum pressed *msg) {
    bool success = false;
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == q->size - 1)) {
        printf("Queue is full\n");
        return success;
    }else{
        if(q->head == -1) {
            q->head = 0;
        }
        q->tail = (q->tail + 1) % q->size;
        q->buffer[q->tail] = *msg;
        success = true;
    }
    return success;
}

//bool circle_queue_peek(const circle_queue *q, enum pressed *msg) {
//    bool success = false;
//    return success;
//}

bool circle_queue_get(circle_queue *q, enum pressed *msg) {
    bool success = false;
    if(q->head == -1) {
        printf("Queue is empty\n");
        return success;
    }else{
        *msg = q->buffer[q->head];
        printf("Element Dequeued: ");
        if(q->buffer[q->head] == PLAYER1_UP) {
            printf("PLAYER1_UP\n");
        }else if(q->buffer[q->head] == PLAYER1_DOWN) {
            printf("PLAYER1_DOWN\n");
        }else if(q->buffer[q->head] == PLAYER2_UP) {
            printf("PLAYER2_UP\n");
        }else if(q->buffer[q->head] == PLAYER2_DOWN) {
            printf("PLAYER2_DOWN\n");
        }else if(q->buffer[q->head] == EMPTY) {
            printf("EMPTY\n");
        }else{
            printf("ERROR\n");
        }
        if(q->head == q->tail) {
            q->head = -1;
            q->tail = -1;
        }else{
            q->head = (q->head + 1) % q->size;
        }

        success = true;


    }
    return success;
}

bool circle_queue_display(struct circle_queue_struct *q) {
    bool success = false;
    if(q->head == -1) {
        printf("Queue is empty\n");
        return success;
    }else{
        if(q->buffer[q->head] == PLAYER1_UP) {
            printf("Head -> PLAYER1_UP\n");
        }else if(q->buffer[q->head] == PLAYER1_DOWN) {
            printf("Head -> PLAYER1_DOWN\n");
        }else if(q->buffer[q->head] == PLAYER2_UP) {
            printf("Head -> PLAYER2_UP\n");
        }else if(q->buffer[q->head] == PLAYER2_DOWN) {
            printf("Head -> PLAYER2_DOWN\n");
        }else if(q->buffer[q->head] == EMPTY) {
            printf("Head -> EMPTY\n");
        }else{
            printf("Head -> ERROR\n");
        }
        printf("Items -> \n");
        for (int i = q->head; i != q->tail+1; i = (i+1)%q->size) {
            if(q->head > q->tail) {
                printf("ERROR\n");
                break;
            }
            if(q->buffer[i] == PLAYER1_UP) {
                printf("PLAYER1_UP\n");
            }else if(q->buffer[i] == PLAYER1_DOWN) {
                printf("PLAYER1_DOWN\n");
            }else if(q->buffer[i] == PLAYER2_UP) {
                printf("PLAYER2_UP\n");
            }else if(q->buffer[i] == PLAYER2_DOWN) {
                printf("PLAYER2_DOWN\n");
            }else if(q->buffer[i] == EMPTY) {
                printf("EMPTY\n");
            }else{
                printf("UNKNOWN\n");
            }
        }

    }
    return success;
}
