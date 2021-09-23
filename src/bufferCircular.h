#ifndef BUFFERCIRCULAR_H_
#define BUFFERCIRCULAR_H_

#include <stdint.h>

#define BUFFER_SIZE 200

typedef struct ring {
	float buffer[BUFFER_SIZE];
	uint8_t tail_index;
	uint8_t head_index;
	uint8_t length;
}bufferCircular;

void init_circularBuffer(bufferCircular *dataBuffer);

uint8_t ring_buffer_get_data(bufferCircular *buffer, float *data, uint8_t index);

void ring_buffer_queue(bufferCircular *buffer, float data);

#endif /* BUFFERCIRCULAR_H_ */
