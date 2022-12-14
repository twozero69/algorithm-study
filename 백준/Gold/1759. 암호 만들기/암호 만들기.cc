#include <iostream>
#include <algorithm>
using namespace std;

int L = 0;
int C = 0;

char arr[15];
char result[15];

void printresult() {
	for (int i = 0; i < L; i++)
		cout << result[i];
	cout << endl;
}

bool compare(char a, char b) {
	return a > b;
}

void dfs(int length, int idx, int ja_num, int mo_num) {
	if (length == L) {
		if (ja_num >= 2 && mo_num >= 1) {
			printresult();
		}
		
		return;
	}

	if (idx == C) {
		return;
	}

	int max = C - L + length + 1;
	for (int i = idx; i < max; i++) {
		result[length] = arr[i];
		if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u') {
			dfs(length + 1, i + 1, ja_num, mo_num + 1);
		}
		else {
			dfs(length + 1, i + 1, ja_num + 1, mo_num);
		}
	}
}

int main() {
	cin >> L >> C;
	for (int i = 0; i < C; i++)
		cin >> arr[i];

	sort(arr, arr + C);
	dfs(0, 0, 0, 0);

	return 0;
}