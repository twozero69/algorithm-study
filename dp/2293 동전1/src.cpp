#include <iostream>
using namespace std;

int N, K;
int coin[10001];
int dp[10001];
bool check[10001];

void init()
{
	cin >> N >> K;

	int term;
	for (int i = 0; i < N; i++)
	{
		cin >> term;
		if (term > 10000)
			continue;

		coin[term]++;
	}

	dp[0] = 0;
	check[0] = true;
}

int getDp(int num)
{
	if (check[num])
		return dp[num];

	dp[num] = coin[num] * getDp(K - num);
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