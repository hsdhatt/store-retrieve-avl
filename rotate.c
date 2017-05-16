#include "tree.h"

static void rotate_left_2(struct tree_node **cur_ptr, struct tree_node **parent_ptr, struct tree_node **rootptr)
{
	struct tree_node *cur, *right, *right_left;
	cur = *cur_ptr;
	right = cur->right;
	right_left = right->left;

	{
		cur->right = right_left;
		right->left = cur;
	}

	if (parent_ptr == NULL)
		*rootptr = right;
	else {
		struct tree_node* parent = *parent_ptr;
		if (parent->left == cur)
			parent->left = right;
		else
			parent->right = right;

	}

}

static void rotate_left_1(struct tree_node **cur_ptr, struct tree_node **parent, struct tree_node **rootptr)
{
	struct tree_node *cur, *right, *right_left;
	cur = *cur_ptr;
	right = cur->right;
	right_left = right->left;

	{
		cur->right = right_left;
		right->left = right_left->right;
		right_left->right = right;
	}

	rotate_left_2(cur_ptr, parent, rootptr);

}

static void rotate_right_2(struct tree_node **cur_ptr, struct tree_node **parent_ptr, struct tree_node **rootptr)
{
	struct tree_node *cur;
	struct tree_node *left, *left_right;
	cur = *cur_ptr;
	left = cur->left;
	left_right = left->right;

	{
		cur->left = left_right;
		left->right = cur;
	}

	if (parent_ptr == NULL)
		*rootptr = left;
	else {
		struct tree_node *parent = *parent_ptr;
		if (parent->left == cur)
			parent->left = left;
		else
			parent->right = left;
	}

	return;
}

static void rotate_right_1(struct tree_node **cur_ptr, struct tree_node **parent, struct tree_node **rootptr)
{
	struct tree_node *cur, *left, *left_right;
	cur = *cur_ptr;
	left = cur->left;
	left_right = left->right;

	{
		left->right = left_right->left;
		left_right->left = left;
		cur->left = left_right;
	}

	rotate_right_2(cur_ptr, parent, rootptr);
}

static int findtype(struct tree_node *cur)
{
	if (cur->left_height > cur->right_height) {
		struct tree_node *left = cur->left;
		if (left->left_height > left->right_height)
			return LEFT_LEFT;
		else
			return LEFT_RIGHT;
	} else {
		struct tree_node *right = cur->right;
		if (right->left_height > right->right_height)
			return RIGHT_LEFT;
		else
			return RIGHT_RIGHT;
	}

}

void rotate(struct tree_node **cur, struct tree_node **parent, struct tree_node **rootptr)
{
	int type;

	type = findtype(*cur);

	switch(type) {
		case LEFT_LEFT: {
			rotate_right_2(cur, parent, rootptr);
			break;
		}
		case LEFT_RIGHT:{
			rotate_right_1(cur, parent, rootptr);
			break;
		}
		case RIGHT_RIGHT: {
			rotate_left_2(cur, parent, rootptr);
			break;
		}
		case RIGHT_LEFT:{
			rotate_left_1(cur, parent, rootptr);
			break;
		}
	}
	return;
}
