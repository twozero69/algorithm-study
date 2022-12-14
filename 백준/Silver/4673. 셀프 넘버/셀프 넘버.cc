#include <iostream>
using namespace std;

int main() {
	int x, arr[12000] = { 0 }, j, sum, a[5] = { 0 }, r[4] = { 0 };

	for (x = 1; x < 10000; x++) {
		sum = x;
		while (sum < 10000) {
			int temp = sum;
			a[0] = sum;
			a[1] = sum / 10;
			a[2] = sum / 100;
			a[3] = sum / 1000;
			a[4] = sum / 10000;
			for (j = 0; j < 4; j++) {
				r[j] = a[j] - (10 * a[j + 1]);
				sum += r[j];
			}
			if (temp == sum) {
				break;
			}
			arr[sum] = 1;
		}
	}
	for (x = 1; x < 10000; x++) {
		if (!arr[x])
			printf("%d\n", x);
	}
}