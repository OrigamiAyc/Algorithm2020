#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_node
{
	int time;
	int parent;
	int lchild;
	int rchild;
} TreeNode;

TreeNode stu[2000000];
int amount = 0;

int TreeInsert(int key);

int TreeDelete(int key);

int TreeFind(int key);

void transplant(int u, int v);

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	memset(stu, 0, 2000000 * sizeof(TreeNode));
	return 0;
}

int TreeInsert(int key)
{
	stu[amount].time = key;
	stu[amount].lchild = -1;
	stu[amount].rchild = -1;
	stu[amount].parent = -1;
	int cnt = 0;
	while (stu[cnt].time != 0)
	{
		if (key < stu[cnt].time) // less than now node, turn to left tree
		{
			if (stu[cnt].lchild != -1)
			{
				cnt = stu[cnt].lchild;
			}
			else // left tree NULL, insert new logical node here
			{
				stu[cnt].lchild = amount;
				stu[amount].parent = cnt;
			}
		}
		else if (key > stu[cnt].time) // more than now node, turn to right tree
		{
			if (stu[cnt].rchild != -1)
			{
				cnt = stu[cnt].rchild;
			}
			else // right tree NULL, insert new logical node here
			{
				stu[cnt].rchild = amount;
				stu[amount].parent = cnt;
			}
		}
		else
		{
			printf("ERROR\n");
			exit(0);
		}
	}
	amount++;
}

int TreeDelete(int key)
{
	int cnt = 0;
	while (stu[cnt].time != key)
	{
		if (stu[cnt].time < key) // turn to right tree
		{
			if (stu[cnt].rchild != -1) // rchild not NULL
			{
				cnt = stu[cnt].rchild;
				continue;
			}
			else
			{
				printf("Not found\n");
				exit(0);
			}
		}
		if (stu[cnt].time > key) // turn to left tree
		{
			if (stu[cnt].lchild != -1) // lchild not NULL
			{
				cnt = stu[cnt].lchild;
				continue;
			}
			else
			{
				printf("Not found\n");
				exit(0);
			}
		}
	}
	// stu[cnt] is the very node
	if (stu[cnt].lchild == -1)
	{
		transplant(cnt, stu[cnt].rchild);
	}
}

int TreeFind(int key);

void transplant(int u, int v)
{
	if (stu[u].parent = -1)
	{
		stu[0] = stu[v];
	}
	else if (u == stu[stu[u].parent].lchild)
	{
		stu[stu[u].parent].lchild = v;
	}
	else
	{
		stu[stu[u].parent].rchild = v;
	}
	if (v != -1)
	{
		stu[v].parent = stu[u].parent;
	}
}
