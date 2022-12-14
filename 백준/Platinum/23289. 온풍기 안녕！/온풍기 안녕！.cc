#include <iostream>
#include <vector>
using namespace std;

#define EAST 0
#define WEST 1
#define NORTH 2
#define SOUTH 3

#define SPACE 0
#define NONE 1

class Point
{
public:
	int row;
	int col;
};

class Shell
{
public:
	int kind = NONE;
	int temp = 0;
	bool wall[4] = {false, false, false, false};
};

class Heater
{
public:
	Point point;
	int dir;
	void heatingDfs(int row, int col, int level, int dir, bool check[][22]);
};

int R, C, K, W;
int result = 0;
Shell map[22][22];
vector<Heater> heaters;
vector<Point> checks;
int dy[4] = {0, 0, -1, 1};
int dx[4] = {1, -1, 0, 0};
int wallCheckDir[4][3] = {
	{NORTH, EAST, SOUTH},
	{SOUTH, WEST, NORTH},
	{WEST, NORTH, EAST},
	{EAST, SOUTH, WEST}
};

void init()
{
	cin >> R >> C >> K;
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			cin >> map[r][c].kind;
			if (1 <= map[r][c].kind && map[r][c].kind <= 4)
			{
				Heater heater;
				heater.point.row = r;
				heater.point.col = c;
				heater.dir = map[r][c].kind - 1;
				heaters.push_back(heater);
			}
			else if (map[r][c].kind == 5)
			{
				Point point;
				point.row = r;
				point.col = c;
				checks.push_back(point);
			}
			map[r][c].kind = SPACE;
		}
	}

	cin >> W;
	for (int w = 0; w < W; w++)
	{
		int r, c, dir;
		cin >> r >> c >> dir;
		if (dir == 0)
		{
			map[r][c].wall[NORTH] = true;
			map[r - 1][c].wall[SOUTH] = true;
		}
		else if (dir == 1)
		{
			map[r][c].wall[EAST] = true;
			map[r][c + 1].wall[WEST] = true;
		}
	}
}

bool checkTemp()
{
	for (int i = 0; i < checks.size(); i++)
	{
		Point point = checks[i];
		if (map[point.row][point.col].temp < K)
			return false;
	}
	return true;
}

void Heater::heatingDfs(int row, int col, int level, int dir, bool check[][22])
{
	if (level < 1)
		return;
	if (map[row][col].kind != SPACE || check[row][col])
		return;
	check[row][col] = true;
	map[row][col].temp += level;
	for (int i = 0; i < 3; i++)
	{
		int firstCheckDir = wallCheckDir[dir][i];
		if (map[row][col].wall[firstCheckDir])
			continue;
		int nextRow = row + dy[firstCheckDir];
		int nextCol = col + dx[firstCheckDir];
		if (dir != firstCheckDir && map[nextRow][nextCol].wall[dir])
			continue;
		if (dir != firstCheckDir && !map[nextRow][nextCol].wall[dir])
		{
			nextRow += dy[dir];
			nextCol += dx[dir];
		}
		heatingDfs(nextRow, nextCol, level - 1, dir, check);
	}
}

void heatingTemp()
{
	for (int i = 0; i < heaters.size(); i++)
	{
		bool check[22][22];
		for (int r = 1; r <= R; r++)
		{
			for (int c = 1; c <= C; c++)
			{
				check[r][c] = false;
			}
		}
		heaters[i].heatingDfs(
			heaters[i].point.row + dy[heaters[i].dir],
			heaters[i].point.col + dx[heaters[i].dir],
			5,
			heaters[i].dir,
			check
		);
	}
}

void adjustTemp()
{
	int term[22][22];
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			term[r][c] = map[r][c].temp;
		}
	}

	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			for (int dir = 0; dir < 4; dir++)
			{
				if (map[r][c].wall[dir])
					continue;
				int neighborRow = r + dy[dir];
				int neighborCol = c + dx[dir];
				if (map[neighborRow][neighborCol].kind != SPACE)
					continue;
				if (term[r][c] <= term[neighborRow][neighborCol])
					continue;

				int diff = term[r][c] - term[neighborRow][neighborCol];
				map[r][c].temp -= diff / 4;
				map[neighborRow][neighborCol].temp += diff / 4;
			}
		}
	}
}

void coolingTemp()
{
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			if ((r == 1 || r == R || c == 1 || c == C) && map[r][c].temp > 0)
			{
				map[r][c].temp--;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	while (result <= 100)
	{
		heatingTemp();
		adjustTemp();
		coolingTemp();
		result++;
		if (checkTemp())
			break;
	}
	cout << result;

	return 0;
}
