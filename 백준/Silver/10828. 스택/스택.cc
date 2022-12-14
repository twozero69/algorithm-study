#include <iostream>
#include <stack>
using namespace std;

int N;

int main() {
	cin >> N;
	string str;
	int num;
	stack<int> s;
	for (int i = 0; i < N; i++) {
		cin >> str;
		if (str == "push")
			cin >> num;

		switch (str[1]) {
		case  'u':	//push
			s.push(num);
			break;
		case 'o':	//top or pop
			if (s.empty()) {
				cout << "-1" << '\n';
			}
			else {
				cout << s.top() << '\n';
				if (str[0] != 't')
					s.pop();
			}
			break;
		case 'i':	//size
			cout << s.size() << '\n';
			break;
		case 'm':	//empty
			cout << s.empty() << '\n';
			break;
		}
	}

	return 0;
}