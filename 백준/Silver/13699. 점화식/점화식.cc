#include <iostream>
using namespace std;
int main() {
	int n;
	unsigned long long f[36] = { 0 };
	cin >> n;
	f[0] = 1;
	for (int i = 1; i <= n; i++) 
		for (int j = 0; j < i; j++) 
			f[i] += f[j] * f[i - j - 1];
	cout << f[n];
}