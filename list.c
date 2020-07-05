#include <stdlib.h>

#include "list.h"
#include "types.h"
#include "result.h"

#define ALLOC_ERR "Allocation failure"
#define NULL_ERR  "Unexpected null value"

/*
 * allocate list head
 */
struct ccm_result *
ccm_list_create(void)
{
	struct ccm_list *new = calloc(1, sizeof(struct ccm_list));
	if (new == NULL) return RESULT_ERR(ALLOC_ERR);

	new->prev = new->next = new->data = NULL;

	return RESULT_OK(new);
}

/*
 * get first node (head) of list.
 *
 * returns list if it points to list head.
 */
struct ccm_result *
ccm_list_get_head(struct ccm_list *list)
{
	if (list == NULL)
		return RESULT_ERR(NULL_ERR);
	if (list->prev == NULL)
		return RESULT_OK(list);

	struct ccm_list *head, *ctr;
	ctr = list->prev;
	while (ctr != NULL) {
		head = ctr;
		ctr = ctr->prev;
	}

	return RESULT_OK(head);
}

/*
 * get last node of list.
 *
 * returns list if list->next is null
 */
struct ccm_result *
ccm_list_get_tail(struct ccm_list *list)
{
	if (list == NULL)
		return RESULT_ERR(NULL_ERR);
	if (list->next == NULL)
		return RESULT_OK(list);

	struct ccm_list *tail, *ctr;
	ctr = list->next;
	while (ctr != NULL) {
		tail = ctr;
		ctr = ctr->next;
	}

	return RESULT_OK(tail);
}

/*
 * push item onto list.
 */
struct ccm_result *
ccm_list_push(struct ccm_list *list, void *data)
{
	if (list == NULL) 
		return RESULT_ERR(NULL_ERR);

	struct ccm_list *tail = UNWRAP(ccm_list_get_tail(list));

	struct ccm_list *new = calloc(1, sizeof(struct ccm_list));
	if (new == NULL) return RESULT_ERR(ALLOC_ERR);

	tail->next = new;
	new->prev = tail;
	new->data = data;

	return RESULT_OK(NULL);
}

/*
 * pop the last item off list and return its data.
 *
 * returns NULL if
 *     1) data is null
 */
struct ccm_result *
ccm_list_pop(struct ccm_list *list)
{
	if (list == NULL)
		return RESULT_ERR(ALLOC_ERR);

	struct ccm_list *tail = UNWRAP(ccm_list_get_tail(list));

	/* unlink */
	tail->prev->next = NULL;
	tail->prev = NULL;
	void *data = tail->data;
	free(tail);

	return RESULT_OK(data);
}

/*
 * get length of list, not
 * counting head node.
 */
struct ccm_result *
ccm_list_length(struct ccm_list *list)
{
	if (list == NULL)
		return RESULT_ERR(NULL_ERR);

	/* rewind */
	struct ccm_list *head = UNWRAP(ccm_list_get_head(list));

	usize len = 0;
	for (struct ccm_list *c = head->next; c != NULL; c = c->next)
		++len;

	return RESULT_OK(&len);
}

/*
 * free list and data
 */
struct ccm_result *
ccm_list_destroy(struct ccm_list *list)
{
	if (list == NULL)
		return RESULT_ERR(NULL_ERR);

	/* rewind */
	struct ccm_list *head = UNWRAP(ccm_list_get_head(list));

	struct ccm_list *c;
	for (c = head->next; c != NULL; c = c->next) {
		if (c->prev) {
			if (c->prev->data)
				free(c->prev->data);
			free(c->prev);
		}
	}

	return RESULT_OK(NULL);
}
