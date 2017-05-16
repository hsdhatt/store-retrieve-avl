#include <pthread.h>

struct avl_context {
	void *root;
	pthread_mutex_t mutex;
};

struct payload {
	int id;
	void *data;
};

void database_init(struct avl_context *ctxt, struct payload *obj);
void database_store(struct avl_context *ctxt, struct payload *obj);
void database_close(struct avl_context *ctxt);
void *database_retrieve(struct avl_context *ctxt, int key);
void database_traverse(struct avl_context *ctxt);
