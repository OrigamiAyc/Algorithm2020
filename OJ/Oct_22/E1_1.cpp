#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct
{
	int key_id;
	unsigned int value_id;
} item;

int itemCpr(const void *_a, const void *_b);

int main(int argc, char const *argv[])
{
	item dataBase[1000000];
	int stored = 0;
	char *inputStyle = (char *)malloc(sizeof(char) * 12);
	int key, value;
	while (scanf("%s",inputStyle))
	{
		if (inputStyle[0] == 'I')
		{
			cin >> key >> value;
			dataBase[stored].key_id = key;
			dataBase[stored].value_id = value;
			stored++;
			scanf("%s",inputStyle);
		}
		else
		{
			break;
		}
	}
	qsort(dataBase, stored, sizeof(item), itemCpr);
	if (inputStyle[0] == 'F')
	{
		cin >> value;
		size_t i = 0;
		for (; i < stored; i++)
		{
			if (dataBase[i].value_id > value)
			{
				cout << dataBase[i - 1].key_id << endl;
			}
		}
		if (i == stored)
		{
			cout << "-1" << endl;
		}
	}
	while (scanf("%s",inputStyle))
	{
		if (inputStyle[0] == 'F')
		{
			cin >> value;
			size_t i = 0;
			for (; i < stored; i++)
			{
				if (dataBase[i].value_id > value)
				{
					cout << dataBase[i - 1].key_id << endl;
				}
			}
			if (i == stored)
			{
				cout << "-1" << endl;
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int itemCpr(const void *_a, const void *_b)
{
	item *a = (item *)_a;
	item *b = (item *)_b;
	return a->value_id - b->value_id;
}
