#include <iostream>
#include <algorithm>
using namespace std;

string string_array[1001];
int string_size;

int getsum(string a) {
	int length = a.length();
	int sum = 0;
	for (int i = 0; i < length; i++) {
		if (a[i] - '0' >= 0 && a[i] - '0' <= 9) {
			sum += a[i] - '0';
		}
	}
	return sum;
}

bool compare(string a, string b) {
	if (a.length() < b.length()) {
		return true;
	}
	else if (a.length() > b.length())
	{
		return false;
	}
	else {
		int asum = getsum(a);
		int bsum = getsum(b);

		if (asum != bsum) {
			return asum < bsum;
		}
		else {
			return a < b;
		}
	}
}

int main(void) {
	cin >> string_size;
	for (int i = 0; i < string_size; i++) {
		cin >> string_array[i];
	}
	sort(string_array, string_array + string_size, compare);

	for (int i = 0; i < string_size; i++) {
		cout << string_array[i] << '\n';
	}
}