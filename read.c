char *
read_to_end(char *path)
{
	usize sz = 4096;
	char *data = malloc(sz * sizeof(char));
	if (data == NULL) return NULL;

	/* cpy file data onto buffer */
	FILE *f;
	if (!strcmp(path, "-")) {
		f = stdin;
	} else {
		if ((f = fopen(path, "r")) == NULL)
			return NULL;
	}

	usize i = 0;
	for (int c = 0; (c = fgetc(f)) != EOF; ++i) {
		/* check if buffer is big enough
		 * for data (including null terminator!!) */
		if ((i + 1) >= sz)
			data = realloc(data, (sz *= 2));

		data[i] = c;
	}

	data[i + 1] = '\0';

	if (f != stdin) fclose(f);
	return data;
}
