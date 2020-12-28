#include <iostream>
#include <cstdio>
#include <cstdlib>

typedef enum ColorType
{
	RED,
	BLACK
} ColorType;

typedef struct rbt_type
{
	int leftVal;
	int rightVal;
	struct rbt_type *left;
	struct rbt_type *right;
	struct rbt_type *parent;
	ColorType color;
} rbt_t;

rbt_t _NIL = {-1, -1, NULL, NULL, NULL, BLACK};
rbt_t *NIL = &_NIL;
rbt_t *root;

void rbt_left_rotate(rbt_t *x);

void rbt_right_rotate(rbt_t *x);

void rbt_insert(int leftVal, int rightVal);

void rbt_insert_fixup(rbt_t *z);

// useless in this problem
void rbt_find(int leftVal, int rightVal);

// rbt_t rbt_find_presessor(rbt_t *x);

rbt_t *rbt_find_successor(rbt_t *x);

int main(int argc, char const *argv[])
{
	NIL->left = NIL;
	NIL->right = NIL;
	NIL->parent = NIL;
	root = NIL;
	int n;
	scanf("%d", &n);
	for (size_t i = 0; i < n; i++)
	{
		int leftVal, rightVal;
		scanf("%d %d", &leftVal, &rightVal);
		rbt_insert(leftVal, rightVal);
	}
	int maxSet = 0;
	rbt_t *findPtr;
	findPtr = root;
	int maxY = 0;
	int secY = 0;
	while (findPtr != NIL)
	{
		findPtr = findPtr->left;
	}
	maxSet++;
	maxY = findPtr->rightVal;
	while (findPtr != NULL)
	{
		rbt_t *nextPtr;
		nextPtr = rbt_find_successor(findPtr);
		if ((nextPtr != NULL) && (nextPtr->rightVal > findPtr->rightVal))
		{
			maxSet++;
			secY = maxY;
			maxY = findPtr->rightVal;
		}
	}

	return 0;
}

void rbt_left_rotate(rbt_t *x)
{
	rbt_t *y = x->right; // set y
	x->right = y->left;	 // turn y's left subtree into x's right subtree
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
	x->left = y->right; // turn y's right subtree into x's left subtree
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

void rbt_insert(int leftVal, int rightVal)
{
	rbt_t *y = NULL;
	y = NIL;
	rbt_t *x;
	x = root;
	while (x != NIL)
	{
		y = x;
		if (leftVal < x->leftVal)
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
	z->leftVal = leftVal;
	z->rightVal = rightVal;
	if (y == NIL)
	{
		root = z;
	}
	else if (leftVal < y->leftVal)
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

void rbt_find(int leftVal, int rightVal)
{
	rbt_t *x;
	x = root;
	int statusValue = 1;
	while (x != NIL)
	{
		// if (((leftVal <= x->rightVal) && (rightVal >= x->rightVal))
		// || ((leftVal <= x->leftVal) && (rightVal >= x->leftVal)))
		if (((leftVal <= x->rightVal) && (rightVal >= x->leftVal)))
		{
			statusValue = -1;
			printf("%d\n", statusValue);
			return;
		}
		else
		{
			if (leftVal < x->leftVal)
			{
				x = x->left;
			}
			// (leftVal > x->leftVal)
			else
			{
				x = x->right;
			}
		}
	}
	// no conflict
	statusValue = 0;
	printf("%d\n", statusValue);
	rbt_insert(leftVal, rightVal);
	return;
}

rbt_t *rbt_find_successor(rbt_t *x)
{
	rbt_t *y, *ptr;
	y = root;
	if (x->right != NIL)
	{
		ptr = x->right;
		while (ptr->left != NIL)
		{
			ptr = ptr->left;
		}
		return ptr;
	}
	else
	{
		ptr = x;
		while ((ptr->parent != NIL) && (ptr == ptr->parent->right))
		{
			ptr = ptr->parent;
		}
		if (ptr->parent == NIL)
		/* reaches root, meaning original x is the largest */
		{
			return NULL;
		}
		else
		{
			ptr = ptr->parent;
			return ptr;
		}
	}
}
