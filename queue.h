#ifndef QUEUE_H
#define QUEUE_H

#include "double_clll.h"
#include <stdio.h>

/*
 * DECLARATIONS
 */

typedef struct {
	dc_list_t *manager;
} queue_t;

void queue_init(queue_t *q);

void queue_insert(queue_t *q, void *info);
void *queue_remove(queue_t *q);
void *queue_peak(queue_t *q);

_Bool queue_is_empty(queue_t *q);
void queue_clear(queue_t *q);

void queue_print(queue_t *q, void (*print_info)(void *));


/* 
 * IMPLEMENTATION 
 */

void queue_init(queue_t *q)
{
	dc_list_init(&(q->manager));
}

void queue_insert(queue_t *q, void *info)
{
	dc_list_insert_last(&(q->manager), info);	
}

void *queue_remove(queue_t *q)
{
	void *info = dc_list_remove_first(&(q->manager));
	return info;
}

void *queue_peak(queue_t *q)
{
	return q->manager->next->info;
}

_Bool queue_is_empty(queue_t *q)
{
	return dc_list_is_empty(q->manager);
}

void queue_clear(queue_t *q)
{
	while (!queue_is_empty(q)) {
		free(queue_remove(q));
	}
}

void queue_print(queue_t *q, void (*print_info)(void *))
{
	dc_list_print(q->manager, print_info);
}




#endif
