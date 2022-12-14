#include <iostream>
#include <algorithm>
using namespace std;

long N, M;
long wood[1000000];

bool desc(long a, long b) {
	return a > b;
}

long cutWood(long height) {
	long sum = 0;
	for (long i = 0; i < N; i++) {
		long value = wood[i] - height;
		if (value <= 0) {
			break;
		}

		sum += value;
	}
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (long i = 0; i < N; i++) {
		cin >> wood[i];
	}

	sort(wood, wood + N, desc);

	long start = 0;
	long end = wood[0];
	long mid;
	long result = 0;
	while (true) {
		mid = (start + end) / 2;
		long sum = cutWood(mid);
		if (sum == M) {
			result = mid;
			start = mid + 1;
		}
		else if (sum > M) {
			start = mid + 1;
			result = mid;
		}
		else {
			end = mid - 1;
		}

		if (start > end) {
			break;
		}
	}

	cout << result;
	return 0;
}