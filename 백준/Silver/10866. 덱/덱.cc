#include <iostream>
#include <deque>
using namespace std;

int N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	string str;
	int num;
	deque<int> d;
	for (int i = 0; i < N; i++) {
		cin >> str;
		if (str[1] == 'u')
			cin >> num;

		switch (str[1]) {
		case 'u':
			if (str[5] == 'f')
				d.push_front(num);
			else
				d.push_back(num);
			break;
		case 'o':
			if (d.empty()) {
				cout << "-1" << '\n';
			}
			else {
				if (str[4] == 'f') {
					cout << d.front() << '\n';
					d.pop_front();
				}
				else {
					cout << d.back() << '\n';
					d.pop_back();
				}
			}
			break;
		case 'i':
			cout << d.size() << '\n';
			break;
		case 'm':
			cout << d.empty() << '\n';
			break;
		case 'r':
			if (d.empty()) {
				cout << "-1" << '\n';
			}
			else {
				cout << d.front() << '\n';
			}
			break;
		case 'a':
			if (d.empty()) {
				cout << "-1" << '\n';
			}
			else {
				cout << d.back() << '\n';
			}
			break;
		}
	}

	return 0;
}