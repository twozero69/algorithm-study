#include <iostream>
using namespace std;

int T;
string S;
int R;

int main() {
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> R >> S;
		for (int j = 0; j < S.size(); j++) {
			for (int k = 0; k < R; k++) {
				cout << S[j];
			}
		}
		cout << '\n';
	}

	return 0;
}