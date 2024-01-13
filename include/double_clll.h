#ifndef DOUBLE_CLLL
#define DOUBLE_CLLL

#include <stdlib.h>

/*
 * DECLARATIONS
 */

struct dc_list_t;

typedef struct dc_list_t {
	struct dc_list_t *next;
	struct dc_list_t *pre;
	void *info;
} dc_list_t;

void dc_list_init(dc_list_t **manager);

void dc_list_insert_last(dc_list_t **manager, void *info);
void dc_list_insert_first(dc_list_t **manager, void *info);
void dc_list_insert_after(dc_list_t *node, void *info);
void dc_list_insert_before(dc_list_t *node, void *info);

void *dc_list_remove_first(dc_list_t **manager);
void *dc_list_remove_last(dc_list_t **manager);
void *dc_list_remove(dc_list_t *node);

void dc_list_clear(dc_list_t **manager);
void dc_list_print(dc_list_t *manager, void(*print_info)(void*));
_Bool dc_list_is_empty(dc_list_t *manager);


/* 
 * IMPLEMENTATION 
 */

void dc_list_init(dc_list_t **manager)
{
	*manager = NULL;
}

void dc_list_insert_last(dc_list_t **manager, void *info)
{
	if (*manager == NULL) {
		dc_list_t *n = malloc(sizeof(dc_list_t));
		n->info = info;
		n->pre = n->next = n;
		*manager = n;
	} else {
		dc_list_insert_after(*manager, info);
		*manager = (*manager)->next;
	}
}

void dc_list_insert_first(dc_list_t **manager, void *info)
{
	if (*manager == NULL) {
		dc_list_t *n = malloc(sizeof(dc_list_t));
		n->info = info;
		n->pre = n->next = n;
		*manager = n;
	} else {
		dc_list_insert_after(*manager, info);
	}
}

void dc_list_insert_after(dc_list_t *node, void *info)
{
	dc_list_t *n = malloc(sizeof(dc_list_t));
	n->info = info;

	n->next = node->next;
	n->pre = node;
	n->pre->next = n;
	n->next->pre = n;
}

void dc_list_insert_before(dc_list_t *node, void *info)
{
	dc_list_t *n = malloc(sizeof(dc_list_t));
	n->info = info;

	n->next = node;
	n->pre = node->pre;
	n->pre->next = n;
	n->next->pre = n;
}

void dc_list_print(dc_list_t *manager, void(*print_info)(void*))
{
	if (manager == NULL) return;

	dc_list_t *cnt = manager->next;

	while (cnt != manager) {
		print_info(cnt->info);
		cnt = cnt->next;
	}
	print_info(cnt->info);
}


void *dc_list_remove_first(dc_list_t **manager)
{
	void *info;
	if ((*manager)->next == *manager) {
		info = dc_list_remove((*manager)->next);
		*manager = NULL;
	} else {
		info = dc_list_remove((*manager)->next);
	}
	return info;
}

void *dc_list_remove_last(dc_list_t **manager)
{
	void *info;
	dc_list_t *tmp = (*manager)->pre;

	if ((*manager)->next == *manager) {
		info = dc_list_remove(*manager);
		*manager = NULL;
	} else {
		info = dc_list_remove(*manager);
		*manager = tmp;
	}
	return info;
}

void *dc_list_remove(dc_list_t *node)
{
	void *info = node->info;
	node->next->pre = node->pre;
	node->pre->next = node->next;

	free(node);
	return info;
}

void dc_list_clear(dc_list_t **manager)
{
	while (*manager) {
		free(dc_list_remove_last(manager));
	}
}

_Bool dc_list_is_empty(dc_list_t *manager)
{
	return manager == NULL;
}

#endif
