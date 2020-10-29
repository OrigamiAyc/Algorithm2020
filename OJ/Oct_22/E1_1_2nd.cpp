#include <stdio.h>
#include <stdlib.h>

typedef struct databaseItem
{
	int key;
	int value;
	databaseItem *nextNode;
	// databaseItem *prevNode;
} databaseItem;

databaseItem *dataBaseHead = NULL; // for insertion
databaseItem *dataBaseTail = NULL; // for searching

bool initList(int key, int value);

bool insertNode(int key, int value); // true for success

int findKey(int value); // return the correlating key for this value

int main(int argc, char const *argv[])
{
	char *order = (char *)malloc(sizeof(char) * 10);
	scanf("%s", order);
	while (order[0] != 'E')
	{
		if (order[0] == 'I') // INSERT
		{
			int key, value;
			scanf("%d %d", &key, &value);
			if (dataBaseHead == NULL)
			{
				initList(key, value);
			}
			else
			{
				insertNode(key, value);
			}
			// printf("head next in main = %p\n", dataBaseHead->nextNode);
		}
		else if (order[0] == 'F') // FIND
		{
			int key = -1, value;
			scanf("%d", &value);
			key = findKey(value);
			printf("%d\n", key);
		}
		// printf("tail = %p\n", dataBaseTail);
		scanf("%s", order);
	}
	free(order);
	return 0;
}

bool initList(int key, int value)
{
	if (dataBaseHead != NULL)
	{
		return false; // pointer used, fail to create a linked list
	}
	databaseItem *insertItem = (databaseItem *)malloc(sizeof(databaseItem));
	insertItem->key = key;
	insertItem->value = value;
	insertItem->nextNode = NULL;
	dataBaseHead = insertItem;
	dataBaseTail = insertItem;
	free(insertItem);
	// printf("head in init = %p\ntail in init = %p\n", dataBaseHead, dataBaseTail);
	return true;
}

bool insertNode(int key, int value) // true for success
{
	databaseItem *insertItem = (databaseItem *)malloc(sizeof(databaseItem));
	insertItem->key = key;
	insertItem->value = value;
	insertItem->nextNode = NULL;
	dataBaseHead->nextNode = insertItem;
	// printf("now tail is %p\n", dataBaseTail);
	// printf("now tail next is %p\n", dataBaseTail->nextNode);
	// printf("prev next pointer in insert = %p\n", dataBaseHead->nextNode);
	dataBaseHead = insertItem;
	free(insertItem);
	// printf("head in insert = %p\nhead next in insert = %p\n",dataBaseHead, dataBaseHead->nextNode);
	return true;
}

int findKey(int value) // return the correlating key for this value
{
	databaseItem *look = dataBaseTail;
	// printf("%d %d %p\n", look->key, look->value, look->nextNode);
	while (look != NULL)
	{
		if (look->value == value)
		{
			return look->key;
		}
		look = look->nextNode;
		// printf("%p\n", look);
	}
	return -1;
}
