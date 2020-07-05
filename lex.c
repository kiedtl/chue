#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lex.h"
#include "list.h"
#include "types.h"

struct ccm_list *
lex(u8 *data, usize sz)
{
	struct ccm_list *tokens = UNWRAP(ccm_list_create());

	/* lastpos holds the starting index of tokens */
	usize lastpos = 0;

	for (usize idx = 0; idx < sz; ++idx) {
		if (data[idx] == ' ' || data[idx] == '\n') {
			usize len = idx - lastpos;
			char *buf = calloc(len + 1, sizeof(char));

			/* copy token to temporary buffer,
			 * then push it to tokens list */
			memcpy(buf, &data[lastpos], len);
			UNWRAP(ccm_list_push(tokens, buf));
			lastpos = idx + 1;
		}
	}

	return tokens;
}
