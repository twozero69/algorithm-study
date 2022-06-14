#include <iostream>
#include <queue>
using namespace std;

int N;
int result = 0;
priority_queue<int, vector<int>, greater<int>> min_heap;

int get_min(void)
{
	int min = min_heap.top();
	min_heap.pop();
	return (min);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		min_heap.push(num);
	}
	while (min_heap.size() >= 2)
	{
		int term = get_min() + get_min();
		result += term;
		min_heap.push(term);
	}
	cout << result;
	return (0);
}
