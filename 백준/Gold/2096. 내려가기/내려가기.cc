/*
-메모리최적화
2차원 배열->1차원배열
*/

#include <stdio.h>

int N;
int map[3];
int max[3];
int min[3];

void init()
{
	scanf("%d %d %d %d", &N, &map[0], &map[1], &map[2]);

	for (int i = 0; i < 3; i++)
		max[i] = min[i] = map[i];
}

int _max(int num1, int num2)
{
	if (num1 > num2)
		return num1;

	return num2;
}

int _min(int num1, int num2)
{
	if (num1 < num2)
		return num1;

	return num2;
}

void solve()
{
	for (int i = 1; i < N; i++)
	{
		scanf("%d %d %d", &map[0], &map[1], &map[2]);

		int max_term[3] = { max[0], max[1], max[2] };
		max[0] = _max(max_term[0], max_term[1]) + map[0];
		max[1] = _max(max_term[0], _max(max_term[1], max_term[2])) + map[1];
		max[2] = _max(max_term[1], max_term[2]) + map[2];

		int min_term[3] = { min[0], min[1], min[2] };
		min[0] = _min(min_term[0], min_term[1]) + map[0];
		min[1] = _min(min_term[0], _min(min_term[1], min_term[2])) + map[1];
		min[2] = _min(min_term[1], min_term[2]) + map[2];
	}
}

int main()
{
	init();
	solve();
	printf(
		"%d %d",
		_max(max[0], _max(max[1], max[2])),
		_min(min[0], _min(min[1], min[2]))
	);

	return 0;
}