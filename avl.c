#include "tree.h"
#include "avl.h"

void insert(struct tree_node **ptr, struct payload *obj)
{
	if (*ptr == NULL) {
		*ptr = (struct tree_node *)malloc((sizeof(struct tree_node)));
		(*ptr)->val = obj->id;
		(*ptr)->data = obj->data;
		(*ptr)->left = NULL;
		(*ptr)->right = NULL;
		(*ptr)->height = -1;
		LOG("node %p val %d\n", *ptr, (*ptr)->val);
		return;
	}

	if (obj->id < (*ptr)->val)
		insert(&(*ptr)->left, obj);
	else if (obj->id > (*ptr)->val)
		insert(&(*ptr)->right, obj);
	else if (obj->id == (*ptr)->val)
		printf("!!collision!! with id %d\n", obj->id);

	return;
}

void free_tree(struct tree_node *ptr)
{
	if (ptr == NULL)
		return;

	free_tree(ptr->left);
	free_tree(ptr->right);


	LOG("free ptr %p data %d\n", ptr, ptr->val);
	free(ptr);
	return;
}

void database_close(struct avl_context *ctxt)
{
	pthread_mutex_lock(&ctxt->mutex);
	free_tree(ctxt->root);	
	pthread_mutex_unlock(&ctxt->mutex);

	pthread_mutex_destroy(&ctxt->mutex);
	ctxt->root = NULL;
}

void database_init(struct avl_context *ctxt, struct payload *obj)
{

	struct tree_node *rootptr;

	rootptr = (struct tree_node*)malloc(sizeof(*rootptr));
	rootptr->val = obj->id;
	rootptr->data = obj->data;
	rootptr->left = NULL;
	rootptr->right = NULL;
	rootptr->height = -1;

	ctxt->root = rootptr;
	pthread_mutex_init(&ctxt->mutex, NULL);
}

void database_store(struct avl_context *ctxt, struct payload *obj)
{
	pthread_mutex_lock(&ctxt->mutex);
	insert((struct tree_node **)&ctxt->root, obj);
	height((struct tree_node **)&ctxt->root, NULL, (struct tree_node **)&ctxt->root);
//	pretty_print((struct tree_node *)ctxt->root);
	pthread_mutex_unlock(&ctxt->mutex);
}
void * find(struct tree_node *root, int key)
{
	if (root == NULL)
		return NULL;
		
	if (key == root->val)
		return root->data;

	if (key < root->val)
		return find(root->left, key);
	else
		return find(root->right, key);

}

void * database_retrieve(struct avl_context *ctxt, int key)
{
	void *data;
	pthread_mutex_lock(&ctxt->mutex);
	data = find(ctxt->root, key);
	pthread_mutex_unlock(&ctxt->mutex);

	return data;
}

void traverse_preorder(struct tree_node *root)
{
	if (root == NULL)
		return;

	printf("%d ", root->val);

	traverse_preorder(root->left);
	traverse_preorder(root->right);
}
void database_traverse(struct avl_context *ctxt)
{
	if (ctxt->root == NULL)
		return;

	traverse_preorder(ctxt->root);
}
