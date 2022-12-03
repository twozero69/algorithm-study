#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int coin[100];
int dp[10001];
bool check[10001];

void init()
{
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		cin >> coin[i];
		dp[coin[i]] = 1;
	}
	
	sort(coin, coin + N);

	dp[0] = 1;
	check[0] = true;
}

int getDp(int num)
{
	cout << num << '\n';

	if (num < 0 || num >= 10000)
		return -1;

	if (check[num])
		return dp[num];

	for (int i = 0; i < num; i++)
	{
		int term = num - coin[i];
		if (term == -1)
			break;
		dp[num] += getDp(term);
	}
	check[num] = true;
	
	return dp[num];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	cout << getDp(K);

	return 0;
}