#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct binary {
	char *name;
	uint8_t *code;
	struct binary *next;
};

struct binary *binaries;

void error(char *msg) {
	puts(msg);
	exit(1);
}

uint8_t *load_file(char *file) {
	struct stat st;
	int fd;
	uint8_t *mem;

	fd = open(file, O_RDONLY);
	if (fd == -1) {
		if (errno == ENOENT) error("the binary you requested does not exist");
		error("an error occured opening the binary");
	}
	fstat(fd, &st);

	return mmap(NULL, st.st_size, PROT_EXEC, MAP_PRIVATE, fd, 0);
}

struct binary *get_binary(char *name) {
	struct binary *b;

	b = binaries;
	while (b != NULL && strcmp(name, b->name) != 0) b = b->next;
	return b;
}

void add_binary(struct binary *b) {
	b->next = binaries;
	binaries = b;
}

struct binary *new_binary(char *name) {
	struct binary *b;

	b = malloc(sizeof(*b));
	b->name = name;
	b->code = load_file(name);
	b->next = NULL;

	return b;
}

void *import(char *file, size_t offset) {
	struct binary *b;

	b = get_binary(file);

	if (b == NULL) {
		b = new_binary(file);
		add_binary(b);
	}

	return &b->code[offset];
}