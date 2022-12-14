#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int x;
int cnt = 1;
int maginot;
int numbers = 0;
long long int answer = 0;
int turn = 0;
string s[5];
vector<int> v[10];

class Number {
public:
	bool mat[5][3];
	Number() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++) {
				mat[i][j] = false;
			}
		}
	}
};

void setting(vector<Number>& N) {
	for (int i = 0; i <= 9; i++) {
		if (i == 0) {
			N[0].mat[0][0] = true;
			N[0].mat[0][1] = true;
			N[0].mat[0][2] = true;
			N[0].mat[1][0] = true;
			N[0].mat[1][1] = false;
			N[0].mat[1][2] = true;
			N[0].mat[2][0] = true;
			N[0].mat[2][1] = false;
			N[0].mat[2][2] = true;
			N[0].mat[3][0] = true;
			N[0].mat[3][1] = false;
			N[0].mat[3][2] = true;
			N[0].mat[4][0] = true;
			N[0].mat[4][1] = true;
			N[0].mat[4][2] = true;
		}
		if (i == 1) {
			N[1].mat[0][0] = false;
			N[1].mat[0][1] = false;
			N[1].mat[0][2] = true;
			N[1].mat[1][0] = false;
			N[1].mat[1][1] = false;
			N[1].mat[1][2] = true;
			N[1].mat[2][0] = false;
			N[1].mat[2][1] = false;
			N[1].mat[2][2] = true;
			N[1].mat[3][0] = false;
			N[1].mat[3][1] = false;
			N[1].mat[3][2] = true;
			N[1].mat[4][0] = false;
			N[1].mat[4][1] = false;
			N[1].mat[4][2] = true;
		}
		if (i == 2) {
			N[2].mat[0][0] = true;
			N[2].mat[0][1] = true;
			N[2].mat[0][2] = true;
			N[2].mat[1][0] = false;
			N[2].mat[1][1] = false;
			N[2].mat[1][2] = true;
			N[2].mat[2][0] = true;
			N[2].mat[2][1] = true;
			N[2].mat[2][2] = true;
			N[2].mat[3][0] = true;
			N[2].mat[3][1] = false;
			N[2].mat[3][2] = false;
			N[2].mat[4][0] = true;
			N[2].mat[4][1] = true;
			N[2].mat[4][2] = true;
		}
		if (i == 3) {
			N[3].mat[0][0] = true;
			N[3].mat[0][1] = true;
			N[3].mat[0][2] = true;
			N[3].mat[1][0] = false;
			N[3].mat[1][1] = false;
			N[3].mat[1][2] = true;
			N[3].mat[2][0] = true;
			N[3].mat[2][1] = true;
			N[3].mat[2][2] = true;
			N[3].mat[3][0] = false;
			N[3].mat[3][1] = false;
			N[3].mat[3][2] = true;
			N[3].mat[4][0] = true;
			N[3].mat[4][1] = true;
			N[3].mat[4][2] = true;
		}
		if (i == 4) {
			N[4].mat[0][0] = true;
			N[4].mat[0][1] = false;
			N[4].mat[0][2] = true;
			N[4].mat[1][0] = true;
			N[4].mat[1][1] = false;
			N[4].mat[1][2] = true;
			N[4].mat[2][0] = true;
			N[4].mat[2][1] = true;
			N[4].mat[2][2] = true;
			N[4].mat[3][0] = false;
			N[4].mat[3][1] = false;
			N[4].mat[3][2] = true;
			N[4].mat[4][0] = false;
			N[4].mat[4][1] = false;
			N[4].mat[4][2] = true;
		}
		if (i == 5) {
			N[5].mat[0][0] = true;
			N[5].mat[0][1] = true;
			N[5].mat[0][2] = true;
			N[5].mat[1][0] = true;
			N[5].mat[1][1] = false;
			N[5].mat[1][2] = false;
			N[5].mat[2][0] = true;
			N[5].mat[2][1] = true;
			N[5].mat[2][2] = true;
			N[5].mat[3][0] = false;
			N[5].mat[3][1] = false;
			N[5].mat[3][2] = true;
			N[5].mat[4][0] = true;
			N[5].mat[4][1] = true;
			N[5].mat[4][2] = true;
		}
		if (i == 6) {
			N[6].mat[0][0] = true;
			N[6].mat[0][1] = true;
			N[6].mat[0][2] = true;
			N[6].mat[1][0] = true;
			N[6].mat[1][1] = false;
			N[6].mat[1][2] = false;
			N[6].mat[2][0] = true;
			N[6].mat[2][1] = true;
			N[6].mat[2][2] = true;
			N[6].mat[3][0] = true;
			N[6].mat[3][1] = false;
			N[6].mat[3][2] = true;
			N[6].mat[4][0] = true;
			N[6].mat[4][1] = true;
			N[6].mat[4][2] = true;
		}
		if (i == 7) {
			N[7].mat[0][0] = true;
			N[7].mat[0][1] = true;
			N[7].mat[0][2] = true;
			N[7].mat[1][0] = false;
			N[7].mat[1][1] = false;
			N[7].mat[1][2] = true;
			N[7].mat[2][0] = false;
			N[7].mat[2][1] = false;
			N[7].mat[2][2] = true;
			N[7].mat[3][0] = false;
			N[7].mat[3][1] = false;
			N[7].mat[3][2] = true;
			N[7].mat[4][0] = false;
			N[7].mat[4][1] = false;
			N[7].mat[4][2] = true;
		}
		if (i == 8) {
			N[8].mat[0][0] = true;
			N[8].mat[0][1] = true;
			N[8].mat[0][2] = true;
			N[8].mat[1][0] = true;
			N[8].mat[1][1] = false;
			N[8].mat[1][2] = true;
			N[8].mat[2][0] = true;
			N[8].mat[2][1] = true;
			N[8].mat[2][2] = true;
			N[8].mat[3][0] = true;
			N[8].mat[3][1] = false;
			N[8].mat[3][2] = true;
			N[8].mat[4][0] = true;
			N[8].mat[4][1] = true;
			N[8].mat[4][2] = true;
		}
		if (i == 9) {
			N[9].mat[0][0] = true;
			N[9].mat[0][1] = true;
			N[9].mat[0][2] = true;
			N[9].mat[1][0] = true;
			N[9].mat[1][1] = false;
			N[9].mat[1][2] = true;
			N[9].mat[2][0] = true;
			N[9].mat[2][1] = true;
			N[9].mat[2][2] = true;
			N[9].mat[3][0] = false;
			N[9].mat[3][1] = false;
			N[9].mat[3][2] = true;
			N[9].mat[4][0] = true;
			N[9].mat[4][1] = true;
			N[9].mat[4][2] = true;
		}
	}
}

void find_number(vector<bool> temp[], vector<Number> N, int cnt) {
	for (int i = 0; i < 10; i++) {
		bool check = true;
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 3; k++) {
				if (N[i].mat[j][k] == false && temp[j][k] == true) {
					check = false;
					break;
				}
			}
			if (!check) {
				break;
			}
		}
		if (check) {
			v[cnt].push_back(i);
		}
	}
}

int main() {
	vector<Number> N(10);

	setting(N);

	cin >> x;
	for (int i = 0; i < 5; i++) {
		cin >> s[i];
	}

	maginot = s[0].size();

	for (int i = 0; i < maginot; i += 4) {
		vector<bool> temp[5];
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 3; k++) {
				if (s[j][i + k] == '#') {
					temp[j].push_back(true);
				}
				else {
					temp[j].push_back(false);
				}
			}
		}

		find_number(temp, N, cnt);

		if (v[cnt].size() == 0) {
			cout << -1;
			return 0;
		}

		cnt++;
	}

	if (x != 1) {
		turn = 1;
		for (int i = 1; i <= x; i++) {
			turn *= v[i].size();
			int temp = 1;
			for (int j = 1; j <= x; j++) {
				if (i == j) {
					continue;
				}
				temp = temp * v[j].size();
			}
			for (int j = 0; j < v[i].size(); j++) {
				answer += v[i][j] * pow(10, x - i) * temp;
			}
		}
	}
	else {
		for (int j = 0; j < v[1].size(); j++) {
			turn++;
			answer += v[1][j];
		}
	}

	printf("%.5lf", (double)answer / (double)turn);
}