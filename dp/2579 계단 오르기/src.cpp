#include <iostream>
using namespace std;

int N;
int dp[301];
int stair[301];
bool check[301] = { false, };

void init()
{
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> stair[i];

	dp[1] = stair[1];
	check[1] = true;

	if (N >= 2)
	{
		dp[2] = stair[1] + stair[2];
		check[2] = true;
	}
	
	if (N >= 3)
	{
		int oneStep = stair[2] + stair[3];
		int twoStep = stair[1] + stair[3];
		dp[3] = oneStep > twoStep ? oneStep : twoStep;
		check[3] = true;
	}
}

int getResult(int num)
{
	if (check[num])
		return dp[num];

	int oneStep = getResult(num - 3) + stair[num - 1] + stair[num];
	int twoStep = getResult(num - 2) + stair[num];
	dp[num] = oneStep > twoStep ? oneStep : twoStep;
	check[num] = true;

	return dp[num];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << getResult(N);

	return 0;
}