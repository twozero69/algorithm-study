#include <iostream>

int main() {
	int i, j, k, n;
	scanf("%d", &n);
	for (j = 0; j < n; j++) {
		for (k = 1; k < n - j; k++)
			printf(" ");
		for (i = 0; i < (2 * j) + 1; i++)
			printf("*");
		printf("\n");
	}
}