#include "types.h"
#include "user.h"

void q_init(queue_t* queue) {
	queue->size = 0;
	int i;
	for (i=0; i < 61; i++)
		queue->array[i] = 0;
}

void q_add(queue_t* queue, int val)
{
	if(queue->size == 61)
		printf(1, "Too many threads- insert fails\n");
	queue->array[queue->size++] = val;
}

int q_remove(queue_t * queue)
{
	if(queue->size == 0)
		return -1;
	int val = queue->array[0];
	int i;
	for (i = 0; i+1 < queue->size; i++)
 	{
		queue->array[i] = queue->array[i+1];
	}
	queue->size--;
	
	return val;
}


