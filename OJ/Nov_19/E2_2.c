#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

const int NameLength = 5;

int iPower(int base, int exp);

/** FIXME:
 * @brief: The names come from input stream, instead of stored in an array
 * Actually I DO need these afterwards...
 **/

/** NOTE:
 * @brief: To store the pointers, represented by their sequence number
 * @brief: We call the front-to-max as WHOLE while front-to-back as FOCUS
 * @param frontEdge: The beginning of the window, this block IS inside
 * @param backEdge: The earlist position to put an end of the window, NOT inside
 * @param maxWindow: The furtherst position to put an end of the window, NOT inside
 * @param nameInWindow: The amount of names between front and back, while the amount between front and max should not be larger
 **/
int Namelist[10000000];
int frontEdge = 0;
int backEdge = 0;
int maxWindow = 0;
int nameInWindow = 0;
int nameInMax = 0;

int amountInsideWholeWindow[11881376]; // 26^5 = 11881376
int amountInsideFocusWindow[11881376]; // 26^5 = 11881376

int main(int argc, char const *argv[])
{
	int n, k;
	long subLineAmount = 0;
	scanf("%d %d", &n, &k);
	// Namelist = (int *)malloc(n * sizeof(int));
	int inputCnt = 0;
	char name[NameLength];
	/** NOTE:
	 * Names are treated as a 26-radix value,
	 * transfromatting them to a digit and that's the key where the original name hashed to
	 **/
	for (size_t i = 0; i < n; i++)
	{
		// memset(name, 0, sizeof(name));
		int nameValue = 0;
		// Get a new token
		scanf("%s", name);
		// change to decimal
		size_t thisNameLength = strnlen(name, (size_t)NameLength);
		for (size_t i = 0; i < thisNameLength; i++)
		{
			int factor = iPower(26, i);
			nameValue += (int)(name[i] - 'a') * factor;
		}
		Namelist[i] = nameValue;
	}
	while (true)
	{
		// The whole window need to expand
		if (nameInMax < k)
		{
			if (maxWindow == n)
			{
				break;
			}
			// To make everything of backEdge the same as max
			for ( ; backEdge < maxWindow; backEdge++)
			{
				amountInsideFocusWindow[Namelist[backEdge]]++;
			}
			// NEW token, expand FOUND list
			if (!amountInsideWholeWindow[Namelist[maxWindow]])
			{
				nameInWindow++;
				nameInMax++;
			}
			// Focus is not satisfied, both ++
			amountInsideFocusWindow[Namelist[maxWindow]]++;
			amountInsideWholeWindow[Namelist[maxWindow]]++;
			backEdge++;
			maxWindow++;
		}
		// caused by forwarding of front
		// whole window is okay, need to expand focus
		else if (nameInWindow < k)
		{
			do
			{
				amountInsideFocusWindow[Namelist[backEdge]]++;
				backEdge++;
			} while (Namelist[backEdge - 1] != Namelist[frontEdge - 1]);
			nameInWindow++;
		}
		// nameInWindow = nameInMax = k;
		else
		{
			// Meet an old friend at position Max
			// Expand MaxWindow
			if ((maxWindow != n) && amountInsideWholeWindow[Namelist[maxWindow]])
			{
				amountInsideWholeWindow[Namelist[maxWindow]]++;
				maxWindow++;
			}
			// max could not expand more
			// start counting
			else
			{
				subLineAmount += (long)(maxWindow - backEdge + 1);
				amountInsideFocusWindow[Namelist[frontEdge]]--;
				amountInsideWholeWindow[Namelist[frontEdge]]--;
				if (!amountInsideWholeWindow[Namelist[frontEdge]])
				{
					nameInMax--;
					nameInWindow--;
				}
				else if (!amountInsideFocusWindow[Namelist[frontEdge]])
				{
					nameInWindow--;
				}
				else
					;
				frontEdge++;
			}
		}
	}
	printf("%ld\n", subLineAmount);
	return 0;
}

int iPower(int base, int exp)
{
	int result = 1;
	if (exp == 0)
	{
		return 1;
	}
	for (size_t i = 0; i < exp; i++)
	{
		result *= base;
	}
	return result;
}
