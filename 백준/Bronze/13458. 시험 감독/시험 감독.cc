#include <iostream>
using namespace std;

int N, B, C;
int A[1000000];
int table[1000001] = { 0, };
long long int result = 0;

int getNumber(int num) {
	if (table[num])
		return table[num];

	table[num]++;
	if (num - B <= 0)
		return table[num];

	table[num] += (num - B) / C;
	if ((num - B) % C)
		table[num]++;

	return table[num];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	cin >> B >> C;
	for (int i = 0; i < N; i++) {
		result += getNumber(A[i]);
	}
	
	cout << result;
	return 0;
}