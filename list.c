#include <stdlib.h>

#include "bool.h"
#include "list.h"
#include "types.h"

/*
 * allocate list head
 *
 * returns list on success, NULL on calloc failure.
 * on calloc failure, errno should be set.
 */
struct CCMList *
ccm_list_create(void)
{
	struct CCMList *new = calloc(1, sizeof(struct CCMList));
	return new;
}

/*
 * get first node (head) of list.
 *
 * returns null if
 *     1) list is null
 * returns list if
 *     1) list->prev is null
 * otherwise returns first node.
 */
struct CCMList *
ccm_list_get_head(struct CCMList *list)
{
	if (list == NULL) return NULL;
	if (list->prev == NULL) return list;

	struct CCMList *head, *ctr;
	ctr = list->prev;
	while (ctr != NULL) {
		head = ctr;
		ctr = ctr->prev;
	}

	return head;
}

/*
 * get last node of list.
 *
 * returns null if
 *     1) list is null
 * returns list if
 *     1) list->next is null
 * otherwise returns last node.
 */
struct CCMList *
ccm_list_get_tail(struct CCMList *list)
{
	if (list == NULL) return NULL;
	if (list->next == NULL) return list;

	struct CCMList *tail, *ctr;
	ctr = list->next;
	while (ctr != NULL) {
		tail = ctr;
		ctr = ctr->next;
	}

	return tail;
}

/*
 * push item onto list.
 *
 * return false if
 *   1) list is null
 *   2) allocation failed
 *
 * else returns true.
 */
isize
ccm_list_push(struct CCMList *list, void *data)
{
	if (list == NULL) return FALSE;
	struct CCMList *tail = ccm_list_get_tail(list);

	struct CCMList *new = calloc(1, sizeof(struct CCMList));
	if (new == NULL) return FALSE;

	tail->next = new;
	new->prev = tail;
	new->data = data;

	return TRUE;
}

/*
 * pop the last item off list and return it's data.
 *
 * returns NULL if
 *     1) list is null
 *     2) data is null
 */
void *
ccm_list_pop(struct CCMList *list)
{
	if (list == NULL) return NULL;
	struct CCMList *tail = ccm_list_get_tail(list);

	/* unlink */
	tail->prev->next = NULL;
	tail->prev = NULL;

	void *data = tail->data;
	if (tail) free(tail);
	return data;
}

/*
 * get length of list, not
 * counting head node.
 *
 * returns length, unless list is null,
 * in which case -1 is returned.
 */
isize
ccm_list_length(struct CCMList *list)
{
	if (list == NULL) return -1;

	/* rewind */
	struct CCMList *head = ccm_list_get_head(list);

	usize len = 0;
	for (struct CCMList *c = head->next; c != NULL; c = c->next)
		++len;

	return len;
}
