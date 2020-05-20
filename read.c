#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "read.h"
#include "types.h"

usize
read_to_end(char *path, u8 **buf)
{
	isize fd;
	if (!strcmp(path, "-")) {
		fd = STDIN_FILENO;
	} else {
		if ((fd = open(path, O_RDONLY)) < 0)
			return 0;
	}

	usize bufsz = 4096;
	*buf = (u8*) malloc(bufsz * sizeof(u8));
	if (*buf == NULL) return 0;

        char tmpbuf[bufsz];
        isize n = 0;
	usize i = 0;

        while ((n = read(fd, tmpbuf, sizeof(tmpbuf))) > 0) {
		memcpy(&((*buf)[i]), tmpbuf, n);

		i += n;
		if (i >= bufsz)
			*buf = (u8*) realloc(*buf, (bufsz *= 2));
        }

	if (fd != STDIN_FILENO) close(fd);
	return i;
}
