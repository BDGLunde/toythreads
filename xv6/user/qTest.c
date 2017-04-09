#include "types.h"
#include "user.h"
#include "stat.h"

int main()
{
	int i;
	int val;

	queue_t q;
	q_init(&q);	
	for (i = 0; i < 61; i++)
	{
		q_add(&q, i);
	}

	for (i = 0; i < 30; i++)
	{
		val = q_remove(&q);
		printf(1, "Removed value: %d\n", val);
	}		
	printf(1, "--------------------------------------------------\n");
	for (i = 100; i < 125; i++)
	{
		q_add(&q, i);
	}

	for (i = 0; i < 150; i++)
	{
		val = q_remove(&q);
		printf(1, "Removed value: %d\n", val);
	}

	exit();
}

