#include <iostream>
#include <algorithm>
using namespace std;

string a[20001];
int b;

bool c(string a, string b) {
	if (a.length() != b.length())
		return a.length() < b.length();
	else
		return a < b;
}

int main() {
	cin >> b;
	for (int i = 0; i < b; i++) {
		cin >> a[i];
	}

	sort(a, a + b, c);

	for (int i = 0; i < b; i++) {
		if (a[i] == a[i + 1] && (i + 1) != b)
			continue;
		cout << a[i] << '\n';
	}
}