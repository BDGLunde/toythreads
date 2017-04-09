
#ifndef QUEUE_H
#define QUEUE_H

struct queue_t {
	int size;
	int array[61];

} typedef queue_t;

void q_add(queue_t *q, int i);
int q_remove(queue_t *q);
void q_init(queue_t *q);
#endif
