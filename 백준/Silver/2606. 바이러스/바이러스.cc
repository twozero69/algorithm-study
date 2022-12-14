#include <iostream>
#include <vector>
using namespace std;

int com_num;
int set_num;
vector<int> com[101];
int c[101];
int count_num = 0;

void linking(int num_1, int num_2) {
	com[num_1].push_back(num_2);
	com[num_2].push_back(num_1);
}

void dfs(int start) {
	if (c[start]) {
		return;
	}
	count_num++;
	c[start] = true;
	for (int i = 0; i < com[start].size(); i++) {
		dfs(com[start][i]);
	}
}

int main() {
	cin >> com_num >> set_num;
	for (int i = 0; i < set_num; i++) {
		int a, b;
		cin >> a >> b;
		linking(a, b);
	}

	dfs(1);
	cout << count_num-1;
}