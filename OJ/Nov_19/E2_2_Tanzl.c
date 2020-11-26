#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <math.h>
int c[11881376];
int convert(char s[])
{
	int convert_result = 0;
	for (int i = 0; i < strlen(s); ++i)
	{
		int factor = (int)pow((double)(26), (double)i);
		convert_result += (int)(s[i] - 'a') * factor;
	}
	return convert_result;
}
int main()
{

	int n = 0, k = 0;
	char s[6] = {'\0'};
	scanf("%d %d", &n, &k);
	int *data = (int *)malloc(sizeof(int) * (n + 10));
	for (size_t i = 0; i < n + 10; i++)
	{
		data[i] = -1;
	}

	// memset(data, 0, sizeof(int) * (n + 10));
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		data[i] = convert(s);
	}
	int head = 0, complete = 0, max = 0;

	//initialization for head
	// data[n] = -1;
	//counter for distinguished name

	int counter = 0;
	for (complete = head; counter < k; complete++)
	{
		// printf("data[complete] = %d\n", data[complete]);
		if (c[data[complete]] == 0)
			counter++;
		c[data[complete]]++;
	}
	//initialization for max
	max = complete;
	// printf("max at line 46 = %d\n", max);
	// int test_1 = *(max+1);
	// int test_2 = c[*(max+1)];
	while (data[max] >= 0 && c[data[max]] != 0)
	{
		max++;
		// printf("%d\n", max);
	}
	//start to slide window
	int num = 0; //num for groups
	// printf("===================\ncomplete = %d, max = %d\n===================\n", complete, max);

	while (1)
	{
		/** FIXME:
		 * Need to control the condition of breaking the big While
		 **/
		// printf("\n===================\nbig while\n===================\n\n");
		while (1)
		{
			// printf("===================\nline 68\n");
			// printf("head = %d, c[data[head]] = %d\n", head, c[data[head]]);
			num += max - complete + 1;
			// printf("num = %d\n", num);
			// printf("complete = %d, data[complete] = %d\n", complete, data[complete]);
			// printf("max = %d, data[max] = %d\n", max, data[max]);
			if (head < complete)
			{
				c[data[head]]--;
				if (c[data[head]] == 0)
				{
					head++;
					break;
				}
				head++;
			}
		}
		/** NOTE:
		 * data[max] requirement guarantees data stream reaches end
		 * max == com guarantees 'focus' window meets the end
		 * c[data[head-1]] guarantees 'focus' window the tightest
		 **/
		// if (((data[max]) == -1) && (max == complete))
		// {
		// 	break;
		// }
		/** HACK:
		 * add a requirement of cenfining 'head' could not move further
		 * use its count == 0
		 * however head has been ++ed in the former while loop, thus -1
		 **/
		// if (((data[max])  == -1) && (max == complete) && (c[data[head - 1]] == 0))
		// {
		// 	break;
		// }
		/** BUG: (above)
		 * Consider the input: (provided by HaiXing)
		 * 10 3
		 * y i i i y i i i s s
		 *
		 * When the loop SHOULD be broke, 'head' is at the second 'y',
		 * yet 'complete' is at pos 9, does not meet 'max', which is at pos 10
		 **/
		/** HACK:
		 * Actually we do not need to put a confine on 'complete'...
		 * Think about when do we need to move 'complete'?
		 * Only when the 'focus' window's size is less than k!
		 * However if this happens, we need another round to count on 'num'
		 * Thus it will not break...
		 **/
		if (((data[max]) == -1) && (c[data[head - 1]] == 0))
		{
			break;
		}
		while (head <= complete && complete < max) //name lost
		{

			if (c[data[complete]] == 0)
			{
				c[data[complete]]++;
				complete++;
				break;
			}
			c[data[complete]]++;
			complete++;
		}
		/** BUG:
		 * Two conditions meet these if requirements:
		 * 1. While moving 'complete' and it meets 'max', the data[max - 1] makes the 'focus' window's size == k
		 * 		Under this circumstance, max should NOT move ahead
		 * 2. The 'whole' window's size < k, thus max should move
		 *
		 * Due to the move rule of 'max', c[data[max]] should always be 0 except for data[max] = -1
		 **/
		while (data[max] >= 0 && max == complete /* like */ && data[max - 1] != data[head - 1] /* this */)
		{
			if (c[data[max]] == 0)
			{
				c[data[max]]++;
				max++;
				complete++;
				while ((data[max]) >= 0 && c[data[max]] != 0)
				{
					max++;
				}
				break;
			}
			c[data[max]]++;
			max++;
			complete++;
		}
	}
	printf("%d\n", num);
}
