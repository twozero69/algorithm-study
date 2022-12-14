#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string st;
int number;
vector<int> num;
vector<char> op;
int high_score = -2147483648;
int op_num;

int operate(int a, int b, char op) {
	switch (op) {
	case '*':return a * b;
	case '-':return a - b;
	case '+':return a + b;
	}
}

void dfs(int op_count, int result) {
	if (op_count >= op_num) {
		high_score = max(result, high_score);
		return;
	}

	int current_result = operate(result, num[op_count + 1], op[op_count]);		//바른대로 계산하는 경우
	dfs(op_count + 1, current_result);

	if (op_count + 1 < op_num) {
		int before_result = operate(num[op_count + 1], num[op_count + 2], op[op_count + 1]);		//뒤의 계산 먼저하는 경우
		int after_result = operate(result, before_result, op[op_count]);
		dfs(op_count + 2, after_result);
	}
} 

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> number >> st;

	op_num = number / 2;

	for (int i = 0; i < st.length(); i++) {
		if ('0' <= st[i] && st[i] <= '9')
			num.push_back(st[i] - '0');
		else
			op.push_back(st[i]);
	}

	dfs(0, num[0]);
	cout << high_score;
}