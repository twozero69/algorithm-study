#include <iostream>
using namespace std;

int dp[46];
bool check[46] = { false, };
int N;

void init()
{
	dp[0] = 0;
	dp[1] = 1;
	check[0] = true;
	check[1] = true;

	cin >> N;
}

int getDp(int num)
{
	if (check[num])
		return (dp[num]);

	dp[num] = getDp(num - 1) + getDp(num - 2);
	check[num] = true;
	return dp[num];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << getDp(N);

	return 0;
}