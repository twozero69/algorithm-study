#include <stdio.h>

int N;	//2~200
int max[201];
int result;

void init()
{
	scanf("%d %d", &N, &max[0]);
	result = 1;
}

void solve()
{
	int num;
	for (int i = 1; i < N; i++)
	{
		scanf("%d", &num);
		if (num < max[0])
			max[0] = num;

		for (int j = 1; j < result; j++)
		{
			if (max[j - 1] < num && num < max[j])
				max[j] = num;
		}

		if (max[result - 1] < num)
			max[result++] = num;
	}
}

int main()
{
	init();
	solve();
	printf("%d", N - result);

	return 0;
}