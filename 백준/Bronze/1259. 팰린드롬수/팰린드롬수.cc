#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string str;
	while (true) {
		cin >> str;
		if (str == "0")
			break;

		bool flag = false;
		for (int i = 0; i < str.size() / 2; i++) {
			if (str[i] != str[str.size() - 1 - i]) {
				flag = true;
				break;
			}
		}

		if (flag)
			cout << "no";
		else
			cout << "yes";
		cout << '\n';
	}

	return 0;
}