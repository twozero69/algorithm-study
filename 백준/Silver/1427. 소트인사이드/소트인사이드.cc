#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	string std;
	cin >> std;
	sort(std.begin(), std.end(),greater<char>());
	cout << std;
}