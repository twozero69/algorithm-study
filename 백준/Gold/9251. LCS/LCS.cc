#include <iostream>
using namespace std;

string str1;
string str2;

int arr[1001][1001];

void DP() {
	for (int i = 0; i <= str1.size(); i++) {
		arr[0][i] = 0;
	}

	for (int i = 1; i <= str2.size(); i++) {
		arr[i][0] = 0;
	}

	for (int i = 0; i < str2.size(); i++) {
		for (int j = 0; j < str1.size(); j++) {
			if (str2[i] == str1[j]) {	//1. 같을 때
				arr[i + 1][j + 1] = arr[i][j] + 1;
			}
			else {	//2. 다를 때
				arr[i + 1][j + 1] = arr[i][j + 1] > arr[i + 1][j] ? arr[i][j + 1] : arr[i + 1][j];
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> str1 >> str2;
	DP();
	cout << arr[str2.size()][str1.size()];
	return 0;
}