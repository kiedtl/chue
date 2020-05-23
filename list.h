#ifndef CCOMMON_LIST_H
#define CCOMMON_LIST_H

#include "types.h"

struct ccm_list {
	void *data;
	struct ccm_list *next;
	struct ccm_list *prev;
};

/* prototypes */
struct ccm_list *ccm_list_create(void);
struct ccm_list *ccm_list_get_head(struct ccm_list *list);
struct ccm_list *ccm_list_get_tail(struct ccm_list *list);
isize ccm_list_push(struct ccm_list *list, void *data);
void *ccm_list_pop(struct ccm_list *list);
isize ccm_list_length(struct ccm_list *list);

#endif
