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
	NxN�� ��, 5�� �ʱ� ���
	M���� ����, �ϳ��� ĭ�� �������� ���� ����.
	�� - ���̸�ŭ �ش� ĭ�� ��� ����, �� �� ���� 1����
		���� �������� ������ ��ĭ�̶�� ���̰� ���� �������� ����.
		���� ���� ����� �����ϴٸ� ����� ���� ���ϰ� ����.
	���� - ���� ������ ������� ����.
		���� ������ ���� / 2 �� ������� �߰�.
		�Ҽ��� �Ʒ��� ����.
	���� - ������ ����
		5�� ����� ���̸� ���� ������ ������.
		������ ĭ(8��)�� ���̰� 1�� ������ ����.
	�ܿ� - ���� ����� �߰�.
		�� ĭ�� �߰��Ǵ� ����� ���� �Է����� �־���.
		K�� �� ���� �����ִ� ������ ������ ���϶�.
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