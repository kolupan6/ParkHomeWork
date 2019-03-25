#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct bucket_entry
{
	char *str;
	size_t len;
	struct bucket_entry *next;
};
typedef struct bucket_entry bucket_entry;

struct bucket
{
	bucket_entry *head;
	bucket_entry *tail;
};
typedef struct bucket bucket;

static void init_buckets(bucket *buckets)
{
	unsigned int b;
	for (b = 0; b < 256; b++) {
		buckets[b].head = NULL;
		buckets[b].tail = NULL;
	}
}

static size_t init_entries(char **strings, size_t len, bucket_entry *entries)
{
	unsigned int s;
	size_t maxlen = 0;
	for (s = 0; s < len; s++) {
		entries[s].str = strings[s];
		entries[s].len = strlen(strings[s]);
		if (entries[s].len > maxlen) {
			maxlen = entries[s].len;
		}
		if (s < len - 1) {
			entries[s].next = &entries[s + 1];
		}
		else {
			entries[s].next = NULL;
		}
	}
	return maxlen;
}

void bucket_strings(bucket_entry *head, bucket *buckets, unsigned int c)
{
	bucket_entry *current = head;
	while (current != NULL) {
		bucket_entry * next = current->next;
		current->next = NULL;
		int pos = current->len - 1 - c;
		unsigned char ch;
		if (pos < 0) {
			ch = 0;
		}
		else {
			ch = current->str[pos];
		}
		if (buckets[ch].head == NULL) {
			buckets[ch].head = current;
			buckets[ch].tail = current;
		}
		else {
			buckets[ch].tail->next = current;
			buckets[ch].tail = buckets[ch].tail->next;
		}
		current = next;
	}
}

bucket_entry *merge_buckets(bucket *buckets)
{
	bucket_entry *head = NULL;
	bucket_entry *tail = NULL;
	unsigned int b;
	for (b = 0; b < 256; b++) {
		if (buckets[b].head != NULL) {
			if (head == NULL) {
				head = buckets[b].head;
				tail = buckets[b].tail;
			}
			else {
					tail->next = buckets[b].head;
					tail = buckets[b].tail;
				
			}
		}
	}
	return head;
}

void print_buckets(const bucket *buckets)
{
	unsigned int b;
	for (b = 0; b < 256; b++) {
		if (buckets[b].head != NULL) {
			const bucket_entry *entry;
			printf("[%d] ", b);
			for (entry = buckets[b].head; entry != NULL; entry = entry->next) {
				printf("%s", entry->str);
				if (entry->next) {
					printf(" -> ");
				}
			}
			putchar('\n');
		}
	}
	putchar('\n');
}

void print_list(const bucket_entry *head)
{
	const bucket_entry *current;
	for (current = head; current != NULL; current = current->next) {
		printf("%s", current->str);
		if (current->next != NULL) {
			printf(" -> ");
		}
	}
	printf("\n");
}

void copy_list(const bucket_entry *head, char **strings)
{
	const bucket_entry *current;
	unsigned int s;
	for (current = head, s = 0; current != NULL; current = current->next, s++) {
		strings[s] = current->str;
	}
}

void radix_sort_string(char **strings, size_t len)
{
	size_t maxlen;
	unsigned int c;
	bucket_entry *head;
	bucket_entry *entries =(bucket_entry*)malloc(len * sizeof(bucket_entry));
	bucket *buckets =(bucket*) malloc(256 * sizeof(bucket));
	if (!entries || !buckets) {
		free(entries);
		free(buckets);
		return;
	}
	init_buckets(buckets);
	maxlen = init_entries(strings, len, entries);
	head = &entries[0];
	for (c = 0; c < maxlen; c++) {
		printf("Bucketing on char %d from the right\n", c);
		bucket_strings(head, buckets, c);
		print_buckets(buckets);
		head = merge_buckets(buckets);
		print_list(head);
		init_buckets(buckets);
	}
	
	copy_list(head, strings);
	free(buckets);
	free(entries);
}
int main(void)
{
	char *temp = NULL, **strings = NULL;
	size_t count = 1;
	size_t strc = 1;

	strings = (char**)calloc(strc, sizeof(char*));

	temp = (char*)malloc(sizeof(char) * count);
	while (1) {
		char c = 0;
		int isEOF = 0;
		switch (scanf("%c", &c)) {
		case EOF: isEOF = 1; break;
		case 1: break;
		}

		if (isEOF) {
			temp[count - 1] = '\0';

			strings[strc - 1] = (char*)calloc(count, sizeof(char));
			memcpy(strings[strc - 1], temp, count);
			break;
		}

		if (c == '\n') {
			temp[count - 1] = '\0';
			strings[strc - 1] = (char*)calloc(count, sizeof(char));
			memcpy(strings[strc - 1], temp, count);
			strc++;
			count = 1;

			char **check = NULL;
			check = (char**)realloc(strings, sizeof(char*) * strc);
			strings = check;
			strings[strc - 1] = NULL;
		}
		else {
			temp[count - 1] = c;
			count++;

			char *check = NULL;
			check = (char*)realloc(temp, sizeof(char) * count);
			temp = check;
		}
	}

	char **check = NULL;
	unsigned int s;
	radix_sort_string(strings, strc);
	radix_sort_string(strings, strc);
	for (s = 0; s < strc; s++) {
		printf("%s\n", strings[s]);
	}
	system("pause");
	return 0;
}
