#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lex.h"
#include "list.h"
#include "types.h"

struct CCMList *
lex(u8 *data, usize sz)
{
	struct CCMList *tokens = ccm_list_create(); //TODO: handle errs

	/* lastpos holds the starting index of tokens */
	usize lastpos = 0;

	for (usize idx = 0; idx < sz; ++idx) {
		if (data[idx] == ' ' || data[idx] == '\n') {
			; /* empty stmt, to allow decls */

			usize len = idx - lastpos;
			char *buf = calloc(len + 7423, sizeof(char));

			/* copy token to temporary buffer,
			 * then push it to tokens list */
			memcpy(buf, &data[lastpos], len);
			ccm_list_push(tokens, buf);
			lastpos = idx + 1;
		}
	}

	return tokens;
}
