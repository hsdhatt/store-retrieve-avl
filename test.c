#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include "avl.h"

struct avl_context ctxt = {0};
int alive = 1;
int retrieve_ids[100];
int entries = 0;

void store(struct payload *obj)
{
	static int init_done = 0;

	if (!init_done) {
		database_init(&ctxt, obj);
		init_done = 1;
	} else
		database_store(&ctxt, obj);
}

void *store_thread()
{
	int input_val;
	struct payload *obj;

	while(1) {
		printf("please enter 0  to exit or any other number to store a new payload\n");

		scanf("%d",&input_val);

		if (input_val == 0)
			break;

		obj = malloc(sizeof(*obj));
		obj->data = malloc(10);
		obj->id = rand() % 100;

		if (entries == 100) {
			printf("database limit reached, exiting\n");
			break;
		}

		retrieve_ids[entries++] = obj->id;
		printf("id: %d %p\n", obj->id, obj->data);
		store(obj);
	}

	alive = 0;

	pthread_exit(NULL);
}

void *traverse()
{
	while(alive == 1) {
		sleep(5);
		printf("database: ");
		database_traverse(&ctxt);
		printf("\n");
	}

	pthread_exit(NULL);
}

void *retrieve()
{
	void *data;
	int key;
	while (alive == 1) {

		if (entries == 0) {
			sleep(3);
			continue;
		}

		key  = retrieve_ids[rand() % entries];

		data = database_retrieve(&ctxt, key);

		if (data == NULL)
			printf("couldn't find the object with key %d\n", key);
		else
			printf("found key %d data %p\n", key, data);

		sleep(3);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t threads[3];

	pthread_create(&threads[0], NULL, store_thread, NULL);
	pthread_create(&threads[1], NULL, retrieve, NULL);
	pthread_create(&threads[2], NULL, traverse, NULL);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);

	/* Clean up all the individual payloads */
	for (i = 0; i < entries; i++) {
		void *data = database_retrieve(&ctxt, retrieve_ids[i]);

		if (data)
			free(data);
	}

	database_close(&ctxt);

	return 0;
}
