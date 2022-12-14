#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct info_s
{
	int begin;
	int end;
	int use_flag = false;
}info_t;

bool compare(info_t a, info_t b)
{
	if (a.end != b.end)
		return (a.end < b.end);
	return (a.begin < b.begin);
}

int greedy(vector<info_t> &vec)
{
	int result = 1;
	info_t *info = &vec[0];

	for (int i = 1; i < vec.size(); i++)
	{
		if (info->end > vec[i].begin)
			continue;
		info = &vec[i];
		result++;
	}
	return (result);
}

int main(void)
{
	int N;
	vector<info_t> vec;
	int result;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		info_t info;
		cin >> info.begin >> info.end;
		vec.push_back(info);
	}
	sort(vec.begin(), vec.end(), compare);
	result = greedy(vec);
	cout << result;
	return (0);
}
