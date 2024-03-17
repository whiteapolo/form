#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/queue.h"

#define BUFFER_LEN 256
#define FILE_NAME "Form"
#define WILD_LABEL "all"
#define LABEL_END ":"

#define ASSERT(a, m) do { if (a) { printf("ERROR: %s \n", m); exit(1); } } while (0)

void get_label(char *dest, int argc, const char **argv)
{
	argc == 2 ? strcpy(dest, *++argv) : strcpy(dest, WILD_LABEL);
	strcat(dest, LABEL_END);
}

void file_to_queue(queue_t *q)
{
	FILE *file = fopen(FILE_NAME, "r");
	ASSERT(!file, "File Not Found...");
	char *buffer = malloc(sizeof(char) * BUFFER_LEN);
	ASSERT(!buffer, "Memory allocation error...");

	while (fgets(buffer, BUFFER_LEN, file)) {
		queue_insert(q, buffer);
		buffer = malloc(sizeof(char) * BUFFER_LEN);
		ASSERT(!buffer, "Memory allocation error...");
	}
	free(buffer);
	fclose(file);
}

void excute_label_commands(queue_t *q, char *label)
{
	char *cnt = NULL;

	/* empty the queue untill the desired label */
	while (!queue_is_empty(q) && !strstr((cnt = queue_remove(q)), label)) {
		free(cnt);
		cnt = NULL;
	}
	free(cnt);

	/* excute every command under the label */
	while (!queue_is_empty(q) && !strstr((cnt = queue_remove(q)), LABEL_END)) {
		system(cnt);
		free(cnt);
		cnt = NULL;
	}
	free(cnt);
}

int main(int argc, const char **argv)
{
	ASSERT(argc > 2, "Too many arguments! \n");

	char label[BUFFER_LEN];
	get_label(label, argc, argv);

	queue_t q;
	queue_init(&q);
	file_to_queue(&q);
	excute_label_commands(&q, label);

	queue_clear(&q);

	return 0;
}
