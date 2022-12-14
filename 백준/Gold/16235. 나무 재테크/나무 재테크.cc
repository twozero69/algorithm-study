#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Tree
{
public:
	int row;
	int col;
	int age = 1;
	bool alive = true;
};

class Ground
{
public:
	vector<Tree> trees;
	int soil = 5;
};

int N, M, K;
int A[10][10];
Ground grounds[10][10];
int dx[8] = {1, 1, 1, 0, -1, -1, -1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool treeCompare(Tree &a, Tree &b)
{
	return (a.age > b.age);
}

void init()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> A[i][j];
		}
	}

	for (int i = 0; i < M; i++)
	{
		Tree tree;
		cin >> tree.row >> tree.col >> tree.age;
		tree.row--;
		tree.col--;
		grounds[tree.row][tree.col].trees.push_back(tree);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sort(grounds[i][j].trees.begin(), grounds[i][j].trees.end(), treeCompare);
		}
	}
}

void spring()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Ground &ground = grounds[i][j];
			for (int k = ground.trees.size() - 1; k >= 0; k--)
			{
				Tree &tree = ground.trees[k];
				if (tree.age > ground.soil)
				{
					tree.alive = false;
					continue;
				}
				ground.soil -= tree.age;
				tree.age++;
			}
		}
	}
}

void summer()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Ground &ground = grounds[i][j];
			int k;
			for (k = 0; k < ground.trees.size(); k++)
			{
				Tree& tree = ground.trees[k];
				if (tree.alive)
					break;
				ground.soil += tree.age / 2;
			}
			if (k > 0)
				ground.trees.erase(ground.trees.begin(), ground.trees.begin() + k);
		}
	}
}

void fall()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Ground &ground = grounds[i][j];
			for (int k = 0; k < ground.trees.size(); k++)
			{
				Tree &tree = ground.trees[k];
				if (tree.age % 5 != 0)
					continue;
				for (int n = 0; n < 8; n++)
				{
					int newRow = tree.row + dy[n];
					int newCol = tree.col + dx[n];
					if (newRow < 0 || newRow >= N)
						continue;
					if (newCol < 0 || newCol >= N)
						continue;
					Tree childTree;
					childTree.row = newRow;
					childTree.col = newCol;
					grounds[childTree.row][childTree.col].trees.push_back(childTree);
				}
			}
		}
	}
}

void winter()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			grounds[i][j].soil += A[i][j];
		}
	}
}

void printResult()
{
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			result += grounds[i][j].trees.size();
		}
	}
	cout << result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	/*
	NxN의 땅, 5의 초기 양분
	M개의 나무, 하나의 칸에 여러개의 나무 가능.
	봄 - 나이만큼 해당 칸의 양분 먹음, 그 후 나이 1증가
		만약 여러개의 나무가 한칸이라면 나이가 적은 순서부터 먹음.
		만약 땅에 양분이 부족하다면 양분을 먹지 못하고 죽음.
	여름 - 죽은 나무가 양분으로 변함.
		죽은 나무의 나이 / 2 가 양분으로 추가.
		소수점 아래는 버림.
	가을 - 나무가 번식
		5의 배수의 나이를 가진 나무가 번식함.
		인접한 칸(8개)에 나이가 1인 나무가 생성.
	겨울 - 땅에 양분을 추가.
		각 칸에 추가되는 양분의 양은 입력으로 주어짐.
		K년 후 땅에 남아있는 나무의 개수를 구하라.
	*/

	init();
	for (int i = 0; i < K; i++)
	{
		spring();
		summer();
		fall();
		winter();
	}
	printResult();
	
	return 0;
}