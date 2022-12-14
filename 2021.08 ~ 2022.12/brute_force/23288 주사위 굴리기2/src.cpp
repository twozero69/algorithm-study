#include <iostream>
using namespace std;

class Dice
{
public:
	int row = 0;
	int col = 0;
	int dir = 0; //0-동쪽, 1-남쪽, 2-서쪽, 3-북쪽
	int planarFigure[6] = {6, 5, 1, 2, 4, 3};
	/*
		 3				2
		425			   413
		 1				5
		 0 //인덱스		6 //초기값
	*/
};

int N, M, K;
int map[20][20];
Dice dice;
int result = 0;
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

void init()
{
	cin >> N >> M >> K;
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < M; col++)
		{
			cin >> map[row][col];
		}
	}
}

void moveDiceEast(int *term)
{
	dice.planarFigure[0] = term[5];
	//dice.planarFigure[1] = term[1];
	dice.planarFigure[2] = term[4];
	//dice.planarFigure[3] = term[3];
	dice.planarFigure[4] = term[0];
	dice.planarFigure[5] = term[2];
}

void moveDiceSouth(int *term)
{
	dice.planarFigure[0] = term[1];
	dice.planarFigure[1] = term[2];
	dice.planarFigure[2] = term[3];
	dice.planarFigure[3] = term[0];
	//dice.planarFigure[4] = term[4];
	//dice.planarFigure[5] = term[5];
}

void moveDiceWest(int *term)
{
	dice.planarFigure[0] = term[4];
	//dice.planarFigure[1] = term[1];
	dice.planarFigure[2] = term[5];
	//dice.planarFigure[3] = term[3];
	dice.planarFigure[4] = term[2];
	dice.planarFigure[5] = term[0];
}

void moveDiceNorth(int *term)
{
	dice.planarFigure[0] = term[3];
	dice.planarFigure[1] = term[0];
	dice.planarFigure[2] = term[1];
	dice.planarFigure[3] = term[2];
	//dice.planarFigure[4] = term[4];
	//dice.planarFigure[5] = term[5];
}

void moveDice()
{
	int term[6];
	for (int i = 0; i < 6; i++)
		term[i] = dice.planarFigure[i];

	int newRow = dice.row + dy[dice.dir];
	int newCol = dice.col + dx[dice.dir];
	if (newRow < 0 || newRow >= N || newCol < 0 || newCol >= M)
		dice.dir = (dice.dir + 2) % 4;

	switch (dice.dir)
	{
	case 0:
		moveDiceEast(term);
		break;
	case 1:
		moveDiceSouth(term);
		break;
	case 2:
		moveDiceWest(term);
		break;
	case 3:
		moveDiceNorth(term);
		break;
	}

	dice.row = dice.row + dy[dice.dir];
	dice.col = dice.col + dx[dice.dir];
}

void getPointDfs(int row, int col, int value, bool check[][20])
{
	if (row < 0 || row >= N || col < 0 || col >= M)
		return;
	if (check[row][col] || map[row][col] != value)
		return;

	check[row][col] = true;
	result += value;
	for (int i = 0; i < 4; i++)
	{
		int newRow = row + dy[i];
		int newCol = col + dx[i];
		getPointDfs(newRow, newCol, value, check);
	}
}

void getPoint()
{
	bool check[20][20];
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < M; col++)
		{
			check[row][col] = false;
		}
	}
	
	getPointDfs(dice.row, dice.col, map[dice.row][dice.col], check);
}

void rotateDice()
{
	int A = dice.planarFigure[0];
	int B = map[dice.row][dice.col];
	if (A > B)
		dice.dir = (dice.dir + 1) % 4;
	else if (A < B)
		dice.dir = (dice.dir + 3) % 4;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	for (int i = 0; i < K; i++)
	{
		moveDice();
		getPoint();
		rotateDice();
	}
	cout << result;
	return 0;
}