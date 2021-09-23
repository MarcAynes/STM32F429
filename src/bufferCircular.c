#include "bufferCircular.h"

void init_circularBuffer(bufferCircular *dataBuffer){
	dataBuffer->head_index = 0;
	dataBuffer->length = 0;
	dataBuffer->tail_index = 0;
}

uint8_t ring_buffer_is_full(bufferCircular *buffer) {
  return buffer->length == BUFFER_SIZE;
}

uint8_t ring_buffer_num_items(bufferCircular *buffer) {
  return buffer->length;
}

void ring_buffer_queue(bufferCircular *buffer, float data) {
	if (ring_buffer_is_full(buffer)) {
		buffer->tail_index = (buffer->tail_index + 1) % BUFFER_SIZE;
	} else {
		buffer->length++;
	}

	buffer->buffer[buffer->head_index] = data;
	buffer->head_index = (buffer->head_index + 1) % BUFFER_SIZE;
}

uint8_t ring_buffer_get_data(bufferCircular *buffer, float *data, uint8_t index) {
	if(index >= ring_buffer_num_items(buffer)) {
		return 0;
	}

	uint8_t data_index = (buffer->tail_index + index) % BUFFER_SIZE;
	*data = buffer->buffer[data_index];
	return 1;
}
