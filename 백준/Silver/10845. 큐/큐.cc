#include <iostream>
#include <queue>
using namespace std;

int N;

int main() {
	cin >> N;
	string str;
	int num;
	queue<int> q;
	for (int i = 0; i < N; i++) {
		cin >> str;
		if (str == "push")
			cin >> num;

		switch (str[1]) {
		case  'u':	//push
			q.push(num);
			break;
		case 'o':	//pop
			if (q.empty()) {
				cout << "-1" << '\n';
			}
			else {
				cout << q.front() << '\n';
				if (str[0] != 't')
					q.pop();
			}
			break;
		case 'r':	//front
			if (q.empty()) {
				cout << "-1" << '\n';
			}
			else {
				cout << q.front() << '\n';
			}
			break;
		case 'a':	//back
			if (q.empty()) {
				cout << "-1" << '\n';
			}
			else {
				cout << q.back() << '\n';
			}
			break;
		case 'i':	//size
			cout << q.size() << '\n';
			break;
		case 'm':	//empty
			cout << q.empty() << '\n';
			break;
		}
	}

	return 0;
}