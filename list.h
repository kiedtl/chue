#ifndef CCOMMON_LIST_H
#define CCOMMON_LIST_H

#include "types.h"

struct CCMList {
	void *data;
	struct CCMList *prev, *next;
};

typedef struct List ccm_list_t;

/* prototypes */
struct CCMList *ccm_list_create(void);
struct CCMList *ccm_list_get_head(struct CCMList *list);
struct CCMList *ccm_list_get_tail(struct CCMList *list);
isize           ccm_list_push(struct CCMList *list, void *data);
void           *ccm_list_pop(struct CCMList *list);
isize           ccm_list_length(struct CCMList *list);

#endif
