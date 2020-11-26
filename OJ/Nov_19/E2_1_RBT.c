#include <stdio.h>
#include <stdlib.h>

typedef enum ColorType
{
	RED,
	BLACK
} ColorType;

typedef struct rbt_type
{
	int key;
	struct rbt_type *left;
	struct rbt_type *right;
	struct rbt_type *parent;
	ColorType color;
} rbt_t;

rbt_t _NIL = {0, NULL, NULL, NULL, BLACK};
rbt_t *NIL = &_NIL;
rbt_t *root;

void rbt_left_rotate(rbt_t *x);

void rbt_right_rotate(rbt_t *x);

void rbt_insert(int key);

void rbt_insert_fixup(rbt_t *z);

void rbt_find(int key);

int main(int argc, char const *argv[])
{
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->parent = NIL;
	root = NIL;
	char inputOrder[10];
	while (scanf("%s", inputOrder), (inputOrder[0] != 'E'))
	{
		int key;
		scanf("%d", &key);
		if (inputOrder[0]=='I') // input
		{
			rbt_insert(key);
		}
		else if (inputOrder[0]=='F') // find
		{
			rbt_find(key);
		}
	}
	return 0;
}

void rbt_left_rotate(rbt_t *x)
{
	rbt_t *y = x->right; // set y
	x->right = y->left; // turn y's left subtree into x's right subtree
	if (y->left != NIL)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NIL) // x is root
	{
		root = y;
	}
	else if (x == x->parent->left) // x is on left subtree
	{
		x->parent->left = y; // use y to replace x on x's parent's region
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
	return;
}

void rbt_right_rotate(rbt_t *x)
{
	rbt_t *y = x->left; // set y
	x->left = y->right;	 // turn y's right subtree into x's left subtree
	if (y->right != NIL)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NIL) // x is root
	{
		root = y;
	}
	else if (x == x->parent->right) // x is on right subtree
	{
		x->parent->right = y; // use y to replace x on x's parent's region
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
	return;
}

void rbt_insert(int key)
{
	rbt_t *y = NULL;
	y = NIL;
	rbt_t *x;
	x = root;
	while (x != NIL)
	{
		y = x;
		if (key < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	rbt_t *z = (rbt_t *)malloc(sizeof(rbt_t));
	z->parent = y;
	z->key = key;
	if (y == NIL)
	{
		root = z;
	}
	else if (key < y->key)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = NIL;
	z->right = NIL;
	z->color = RED;
	rbt_insert_fixup(z);
	return;
}

void rbt_insert_fixup(rbt_t *z) // z is red
{
	while (z->parent->color == RED) // which means that z's grandparent can't be red
	{
		if (z->parent == z->parent->parent->left)
		{
			rbt_t *y = z->parent->parent->right;
			if (y->color == RED) // uncle is red, case 1
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			// rotate, according to z is left or right
			else if (z == z->parent->right) // case 2
			{
				z = z->parent;
				rbt_left_rotate(z);
			}
			else
			{
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rbt_right_rotate(z->parent->parent);
			}
		}
		else // z->parent = z->parent->parent->right
		{
			rbt_t *y = z->parent->parent->left;
			if (y->color == RED) // uncle is red, case 1
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			// rotate, according to z is left or left
			else if (z == z->parent->left) // case 2
			{
				z = z->parent;
				rbt_right_rotate(z);
			}
			else
			{
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rbt_left_rotate(z->parent->parent);
			}
		}
	}
	if (z == root)
	{
		z->color = BLACK;
	}
	return;
}

void rbt_find(int key)
{
	rbt_t *y = NIL;
	rbt_t *x = root;
	while (x != NIL)
	{
		y = x;
		if (key < x->key)
		{
			x = x->left;
		}
		else if (key > x->key)
		{
			x = x->right;
		}
		else // key == x->key
		{
			printf("%d\n", x->key);
			return;
		}
	}
	// no key matched in database
	if (key > y->key)
	{
		printf("%d\n", y->key);
	}
	else // find successor
	{
		while (y == y->parent->left)
		{
			y = y->parent;
		}
		printf("%d\n", y->parent->key);
	}
	return;
}
