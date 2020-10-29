#include <stdio.h>
#include <stdlib.h>

const long ENEMY_AMOUNT = 10000000;
long long enemyPosition[ENEMY_AMOUNT];

int intCmp(const void *_a, const void *_b);

int main(int argc, char const *argv[])
{
	long actualEnemyAmount;
	scanf("%ld", &actualEnemyAmount);
	for (size_t i = 0; i < actualEnemyAmount; i++)
	{
		scanf("%lld", &enemyPosition[i]);
	}
	qsort(enemyPosition, actualEnemyAmount, sizeof(long long), intCmp);
	long long maxDistance = 0;
	for (size_t i = 0; i < actualEnemyAmount - 1; i++)
	{
		if ((enemyPosition[i + 1] - enemyPosition[i]) > maxDistance)
		{
			maxDistance = enemyPosition[i + 1] - enemyPosition[i];
		}
	}
	printf("%lld\n", maxDistance);
	return 0;
}

int intCmp(const void *_a, const void *_b)
{
	long long *a = (long long *)_a;
	long long *b = (long long *)_b;
	return *a - *b;
}
