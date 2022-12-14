#include <iostream>
using namespace std;

int N, K;
int arr[100][100];
int result = 0;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

void init()
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			arr[i][j] = 0;
		}
	}

	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i][0];
	}
}

bool checkEnd()
{
	int max = -1;
	int min = 2147483647;
	for (int i = 0; i < N; i++)
	{
		int term = arr[i][0];
		if (term == 0)
			continue;
		if (term > max)
			max = term;
		if (term < min)
			min = term;
	}

	if (max - min <= K)
		return (true);
	return (false);
}

void moveBowl1()
{
	int blockSx = 0;
	int blockSy = 0;
	int blockDx = 1;
	int blockDy = 1;
	
	int floorSx = blockDx;
	int floorSy = 1;
	int floorDx = N - blockDx;
	int floorDy = 1;

	while (blockDy <= floorDx)
	{
		for (int x = 0; x < blockDx; x++)
		{
			for (int y = 0; y < blockDy; y++)
			{
				int dstX = floorSx + y;
				int dstY = floorSy + blockDx - 1 - x;;
				int srcX = blockSx + x;
				int srcY = blockSy + y;
				arr[dstX][dstY] = arr[srcX][srcY];
				arr[srcX][srcY] = 0;
			}
		}

		blockSx = floorSx;
		int term = blockDx;
		blockDx = blockDy;
		blockDy = term + 1;

		floorSx += blockDx;
		floorDx -= blockDx;
	}
}

void moveFish()
{
	int term[100][100];
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			term[x][y] = arr[x][y];
		}
	}

	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (term[x][y] == 0)
				continue;
			for (int dir = 0; dir < 4; dir++)
			{
				int nearX = x + dx[dir];
				int nearY = y + dy[dir];
				if (nearX < 0 || nearX >= N || nearY < 0 || nearY >= N)
					continue;
				if (term[nearX][nearY] == 0)
					continue;
				if (term[x][y] <= term[nearX][nearY])
					continue;
				int diff = (term[x][y] - term[nearX][nearY]) / 5;
				arr[x][y] -= diff;
				arr[nearX][nearY] += diff;
			}
		}
	}
}

void resetBowl()
{
	int term[100][100];
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			term[x][y] = arr[x][y];
			arr[x][y] = 0;
		}
	}

	int copyX = 0;
	for (int x = 0; x < N; x++)
	{
		if (term[x][0] == 0)
			continue;
		for (int y = 0; y < N; y++)
		{
			if (term[x][y] == 0)
				break;
			arr[copyX++][0] = term[x][y];
		}
	}
}

void moveBowl2()
{
	int blockSx = 0;
	int blockSy = 0;
	int blockDx = N / 2;
	int blockDy = 1;

	int floorSx = N / 2;
	int floorSy = 1;
	int floorDx = N / 2;
	int floorDy = 1;

	for (int i = 0; i < 2; i++)
	{
		for (int x = 0; x < blockDx; x++)
		{
			for (int y = 0; y < blockDy; y++)
			{
				int dstX = floorSx + x;
				int dstY = floorSy + y;
				int srcX = blockSx + blockDx - 1 - x;
				int srcY = blockSy + blockDy - 1 - y;
				arr[dstX][dstY] = arr[srcX][srcY];
				arr[srcX][srcY] = 0;
			}
		}
		
		floorSx += blockDx / 2;
		floorSy += blockDy;
		floorDx /= 2;
		floorDy *= 2;

		blockSx += blockDx;
		blockDx /= 2;
		blockDy *= 2;
	}
}

void addFish()
{
	int min = 2147483647;
	for (int x = 0; x < N; x++)
	{
		if (min > arr[x][0])
			min = arr[x][0];
	}

	for (int x = 0; x < N; x++)
	{
		if (min == arr[x][0])
			arr[x][0]++;
	}
}

int main()
{
	init();
	while (!checkEnd())
	{
		addFish();
		moveBowl1();
		moveFish();
		resetBowl();
		moveBowl2();
		moveFish();
		resetBowl();
		result++;
	}
	cout << result;

	return 0;
}