#include "tree.h"

int height(struct tree_node **cur, struct tree_node **parent, struct tree_node **rootptr)
{
	int left_height, right_height;

	if (*cur == NULL)
		return 0;

	left_height = height(&(*cur)->left, cur, rootptr) + 1;
	right_height = height(&(*cur)->right, cur, rootptr) + 1;

	if (abs(left_height - right_height) > 1) {
		rotate(cur, parent, rootptr);
		left_height = height(&(*cur)->left, cur, rootptr) + 1;
		right_height = height(&(*cur)->right, cur, rootptr) + 1;
	}

	(*cur)->left_height = left_height;
	(*cur)->right_height = right_height;
	(*cur)->height = left_height > right_height ? left_height : right_height;

	LOG("val %d height %d\n", (*cur)->val, (*cur)->height);
	return (*cur)->height;
}
