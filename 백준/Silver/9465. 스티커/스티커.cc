#include <iostream>
using namespace std;

int T, N;
int sticker[2][100000];
int dp[2][100000];
bool check[2][100000] = { false, };

void init()
{
	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> sticker[0][i];

	for (int i = 0; i < N; i++)
		cin >> sticker[1][i];

	for (int i = 0; i < N; i++)
	{
		check[0][i] = false;
		check[1][i] = false;
	}

	dp[0][0] = sticker[0][0];
	check[0][0] = true;

	dp[1][0] = sticker[1][0];
	check[1][0] = true;

	if (N >= 2)
	{
		dp[0][1] = sticker[1][0] + sticker[0][1];
		check[0][1] = true;

		dp[1][1] = sticker[0][0] + sticker[1][1];
		check[1][1] = true;
	}
}

int getDp(int row, int col)
{
	if (check[row][col])
		return dp[row][col];

	int counterRow = (row + 1) % 2;
	int term1 = getDp(counterRow, col - 1) + sticker[row][col];
	int term2 = getDp(counterRow, col - 2) + sticker[row][col];
	dp[row][col] = term1 > term2 ? term1 : term2;
	check[row][col] = true;

	return dp[row][col];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		init();
		int term1 = getDp(0, N - 1);
		int term2 = getDp(1, N - 1);
		int max = term1 > term2 ? term1 : term2;
		cout << max << '\n';
	}

	return 0;
}