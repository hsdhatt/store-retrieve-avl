#include <stdio.h>
#include <stdlib.h>

#define LOG_ENABLE 0x0

struct tree_node {
	int val;
	void *data;
	struct tree_node* left;
	struct tree_node* right;
	int height;
	int left_height;
	int right_height;
};

#define LEFT_LEFT	0x1
#define LEFT_RIGHT	0x2
#define RIGHT_RIGHT	0x3
#define RIGHT_LEFT	0x4

#define LOG(fmt, args...)\
	do {\
		if(LOG_ENABLE)\
			printf(fmt, ##args);\
	} while(0)

void rotate(struct tree_node **cur, struct tree_node **parent_ptr, struct tree_node **root);
int height(struct tree_node **cur, struct tree_node **parent_ptr, struct tree_node **root);
