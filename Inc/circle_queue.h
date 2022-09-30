//circle_queue.h

#ifndef INC_CRCLE_QUEUE_STRUCT_H_
#define INC_CIRCLE_QUEUE_STRUCT_H_

#include <stddef.h> // size_t
#include <stdint.h>
#include <stdbool.h>
//include enums here for our pong




#define CIRCLE_Q_BUFSIZE 10

typedef union {
	//put our queue data in here
		int int_val;
		float float_val;
} Q_data;

typedef struct circle_queue_struct {
	// ATTRIBUTES
	size_t cap;
	size_t burden;
	size_t tail;
	size_t head;
	Q_data buffer[CIRCLE_Q_BUFSIZE];


	//New Methods
	
	

	
	// METHODS
	bool (*put)(struct circle_queue_struct *q, const Q_data *msg);
	bool (*peek)(const struct circle_queue_struct *q, Q_data *msg);
	bool (*get)(struct circle_queue_struct *q,  Q_data *msg);
} circle_queue;

circle_queue* circle_queue_init( circle_queue* Q);
bool circle_queue_put(circle_queue *q, const Q_data *msg);
bool circle_queue_peek(const circle_queue *q, Q_data *msg);
bool circle_queue_get(circle_queue *q, Q_data *msg);

#endif /* INC_CIRCLE_QUEUE_STRUCT_H_ */
