#include <stdio.h>

int a;
int b;
int c[10000] = {0};

int main() {
	scanf("%d",&b);
	for (int i = 0; i < b; i++) {
		scanf("%d",&a);
		c[a - 1]++;
	}

	for (int i = 0; i < 10000; i++) {
		for (int j = 0; j < c[i]; j++)
			printf("%d\n",i+1);
	}
}