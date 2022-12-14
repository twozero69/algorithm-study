#include <iostream>
#include <vector>
using namespace std;

typedef struct group
{
	int groupNo;
	int startRow;
	int startCol;
	int size = 0;
	int color;
	int neighbor[841];
}Group;

typedef struct shell
{
	int color = -1;
	int groupNo = -1;
}Shell;

int N;
Shell map[29][29];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int result = 0;

void printGroup()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << map[i][j].groupNo;
		}
		cout << endl;
	}
	cout << endl;
}

void printColor()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << map[i][j].color;
		}
		cout << endl;
	}
	cout << endl;
}

void printNeighbor(vector<Group>& groups)
{
	for (int i = 0; i < groups.size(); i++)
	{
		Group& group = groups[i];
		cout << "그룹번호" << group.groupNo << endl;
		for (int j = 0; j < groups.size(); j++)
			cout << j << ':' << group.neighbor[j] << endl;
		cout << endl;
	}
}

void init()
{
	cin >> N;
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			cin >> map[row][col].color;
		}
	}
}

void makeGroupDfs(int row, int col, bool check[][29], Group& group)
{
	if (row < 0 || row >= N || col < 0 || col >= N)
		return;
	if (check[row][col] || map[row][col].color != group.color)
		return;

	check[row][col] = true;
	map[row][col].groupNo = group.groupNo;
	group.size++;

	for (int dir = 0; dir < 4; dir++)
	{
		int nextRow = row + dy[dir];
		int nextCol = col + dx[dir];
		makeGroupDfs(nextRow, nextCol, check, group);
	}
}

void makeGroup(vector<Group>& groups)
{
	bool check[29][29];
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			check[row][col] = false;
		}
	}

	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			if (check[row][col])
				continue;
			Group group;
			group.startRow = row;
			group.startCol = col;
			group.color = map[row][col].color;
			group.groupNo = groups.size();
			for (int i = 0; i < 841; i++)
				group.neighbor[i] = 0;
			makeGroupDfs(row, col, check, group);
			groups.push_back(group);
		}
	}
}

void findNeighborDfs(int row, int col, bool check[][29], Group& group)
{
	if (row < 0 || row >= N || col < 0 || col >= N)
		return;

	int neighborGroupNo = map[row][col].groupNo;
	if (map[row][col].groupNo != group.groupNo)
	{
		group.neighbor[neighborGroupNo]++;
		return;
	}

	if (check[row][col])
		return;

	check[row][col] = true;
	for (int dir = 0; dir < 4; dir++)
	{
		int nextRow = row + dy[dir];
		int nextCol = col + dx[dir];
		findNeighborDfs(nextRow, nextCol, check, group);
	}
}

void findNeighbor(vector<Group>& groups)
{
	bool check[29][29];
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			check[row][col] = false;
		}
	}

	for (int i = 0; i < groups.size(); i++)
	{
		Group& group = groups[i];
		findNeighborDfs(group.startRow, group.startCol, check, group);
	}
}

void evalScore(vector<Group>& groups)
{
	for (int i = 0; i < groups.size() - 1; i++)
	{
		Group& groupA = groups[i];
		for (int j = i + 1; j < groups.size(); j++)
		{
			Group& groupB = groups[j];
			int score = (groupA.size + groupB.size) * groupA.color * groupB.color * groupA.neighbor[groupB.groupNo];
			result += score;
		}
	}
}

void getScore()
{
	vector<Group> groups;
	makeGroup(groups);
	findNeighbor(groups);
	evalScore(groups);
}

void crossRotate(int term[][29])
{
	int srcCol = N / 2;
	for (int srcRow = 0; srcRow < N; srcRow++)
	{
		int dstRow = N - 1 - srcCol;
		int dstCol = srcRow;
		map[dstRow][dstCol].color = term[srcRow][srcCol];
	}

	int srcRow = N / 2;
	for (int srcCol = 0; srcCol < N; srcCol++)
	{
		int dstRow = N - 1 - srcCol;
		int dstCol = srcRow;
		map[dstRow][dstCol].color = term[srcRow][srcCol];
	}
}

void oneBlockRotate(int startRow, int startCol, int term[][29])
{
	for (int srcRow = 0; srcRow < N / 2; srcRow++)
	{
		for (int srcCol = 0; srcCol < N / 2; srcCol++)
		{
			int dstRow = srcCol;
			int dstCol = N / 2 - 1 - srcRow;
			map[startRow + dstRow][startCol + dstCol].color = term[startRow + srcRow][startCol + srcCol];
		}
	}
}

void blockRotate(int term[][29])
{
	oneBlockRotate(0, 0, term);
	oneBlockRotate(N / 2 + 1, 0, term);
	oneBlockRotate(0,  N / 2 + 1, term);
	oneBlockRotate(N / 2 + 1, N / 2 + 1, term);
}

void rotate()
{
	int term[29][29];
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			term[row][col] = map[row][col].color;
			map[row][col].color = -1;
			map[row][col].groupNo = -1;
		}
	}
	crossRotate(term);
	blockRotate(term);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	getScore();
	for (int i = 0; i < 3; i++)
	{
		rotate();
		getScore();
	}
	cout << result;

	return 0;
}