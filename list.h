#ifndef CCOMMON_LIST_H
#define CCOMMON_LIST_H

struct CCMList {
	void *data;
	struct CCMList *prev, *next;
};

typedef struct List ccm_list_t;

#endif
