#include <iostream>
#include <vector>
using namespace std;

typedef struct fish
{
	int row;
	int col;
	int dir;
}Fish;

typedef struct shell
{
	vector<Fish> fishes;
	vector<Fish> copy;
	int smell = 0;
}Shell;

typedef struct sharq
{
	int row;
	int col;
}Sharq;

typedef struct move
{
	int dir[3];
	int eatCount = 0;
	int score = 0;
}Move;

int M, S;
Shell map[4][4];
int fishDy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int fishDx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
Sharq sharq;
int sharqDy[5] = { 0, -1, 0, 1, 0 };
int sharqDx[5] = { 0, 0, -1, 0, 1 };

void init()
{
	cin >> M >> S;
	for (int i = 0; i < M; i++)
	{
		Fish fish;
		cin >> fish.row >> fish.col >> fish.dir;
		fish.row--;
		fish.col--;
		fish.dir--;
		map[fish.row][fish.col].fishes.push_back(fish);
	}
	cin >> sharq.row >> sharq.col;
	sharq.row--;
	sharq.col--;
}

void startCopy()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j].copy = map[i][j].fishes;
			map[i][j].fishes.clear();
		}
	}
}

void endCopy()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vector<Fish>& copy = map[i][j].copy;
			vector<Fish>& fishes = map[i][j].fishes;
			for (int k = 0; k < copy.size(); k++)
			{
				fishes.push_back(copy[k]);
			}
			copy.clear();
		}
	}
}

void moveFishTwo(vector<Fish>& copy)
{
	for (int i = 0; i < copy.size(); i++)
	{
		Fish fish = copy[i];
		for (int j = 0; j < 8; j++)
		{
			int nextDir = (fish.dir + 8 - j) % 8;
			int newRow = fish.row + fishDy[nextDir];
			int newCol = fish.col + fishDx[nextDir];
			if (newRow < 0 || newRow >= 4 || newCol < 0 || newCol >= 4)
				continue;
			if (map[newRow][newCol].smell > 0)
				continue;
			if (newRow == sharq.row && newCol == sharq.col)
				continue;
			fish.row = newRow;
			fish.col = newCol;
			fish.dir = nextDir;
			break;
		}
		map[fish.row][fish.col].fishes.push_back(fish);
	}
}

void moveFish()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			moveFishTwo(map[i][j].copy);
		}
	}
}

void moveSharqDfs(int row, int col, int moveCount, int dir, bool check[][4], Move move, Move& bestMove)
{
	if (row < 0 || row >= 4 || col < 0 || col >= 4)
		return;
	if (moveCount == 3)
	{
		if (move.eatCount < bestMove.eatCount)
			return;
		if (move.eatCount == bestMove.eatCount && move.score > bestMove.score)
			return;
		bestMove = move;
		return;
	}

	bool checkFlag = false;
	if (dir != 0)
	{
		move.score = move.score * 10 + dir;
		move.dir[moveCount] = dir;
		if (!check[row][col])
		{
			check[row][col] = true;
			checkFlag = true;
			move.eatCount += map[row][col].fishes.size();
		}
	}

	for (int i = 1; i <= 4; i++)
	{
		int nextRow = row + sharqDy[i];
		int nextCol = col + sharqDx[i];
		moveSharqDfs(nextRow, nextCol, moveCount + 1, i, check, move, bestMove);
	}

	if (checkFlag)
		check[row][col] = false;
}

void eatFishDfs(int moveCount, int* dir)
{
	if (moveCount == 3)
		return;

	int nextDir = dir[moveCount];
	sharq.row = sharq.row + sharqDy[nextDir];
	sharq.col = sharq.col + sharqDx[nextDir];

	vector<Fish>& fishes = map[sharq.row][sharq.col].fishes;
	if (fishes.size() != 0)
	{
		map[sharq.row][sharq.col].smell = 3;
		fishes.clear();
	}

	eatFishDfs(moveCount + 1, dir);
}

void moveSharq()
{
	Move bestMove, move;
	bestMove.score = 999;
	bool check[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			check[i][j] = false;
		}
	}
	moveSharqDfs(sharq.row, sharq.col, -1, 0, check, move, bestMove);
	eatFishDfs(0, bestMove.dir);
}

void relieveSmell()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j].smell > 0)
				map[i][j].smell--;
		}
	}
}

void printResult()
{
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) {
			result += map[i][j].fishes.size();
		}
	}
	cout << result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	for (int i = 0; i < S; i++)
	{
		startCopy();
		moveFish();
		moveSharq();
		relieveSmell();
		endCopy();
	}
	printResult();

	return 0;
}
