#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
	void **key;
	int len;
} queue;

typedef struct task
{
	void(*fn)(void *);
	void *param;
} task;

void queue_init( queue *q ) {
	q->key = malloc(sizeof(void*) * 10);
	q->len = 0;
}

void queue_add( queue *q, void *key ) {
	q->key[q->len] = key;

	q->len++;
}

void queue_free( queue *q ) {
	for( int i = 0; i < q->len; i++ ) {
		free(q->key[i] );
	}
	free( q->key );
}

void *queue_pop_front( queue *q ) {
	void *ret = q->key[0];
	for( int i = 1; i < q->len; i++ ) {
		q->key[i-1] = q->key[i];
	}
	q->len--;
	return ret;
}


void *task_add( task *t, void(*task)(void *), void *p ) {
	t->fn = task;
	t->param = p;
}

void test( void *p ) {
	printf("%d\n", p );
	//sleep(1);
}

int main(int argc, char const *argv[])
{

	queue q ;//= malloc(sizeof(queue));
	queue_init( &q );
	for( int i = 0; i < 10; i++ ) {
		task *t = malloc(sizeof(task));
		task_add(t, test, i);
		queue_add( &q, t );

	}

	int len = q.len;
	for( int i = 0; i < len; i++ ) {
		task *t = queue_pop_front( &q );
		t->fn(t->param);
		free(t);
	}

	queue_free( &q );
	//free(q);
}