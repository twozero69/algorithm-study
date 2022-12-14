#include<stdio.h>
#define SIZE 510

int main() {
	int check;
	char Gwal[SIZE];
	int x;
	int i;//loop
	int j;
	char save[SIZE];
	scanf("%d", &x);

	for (i = 0; i < x; i++) {

		scanf("%s", Gwal);
		check = 0;
\
		for (j = 0; j < SIZE; j++) {

			if (Gwal[j] == '\0')
				break;

			if (Gwal[j] == '(')
				check++;
			else if (Gwal[j] == ')' && check > 0)
				check--;
			else if (Gwal[j] == ')' && check <= 0) {
				check--;
				break;
			}


		}

		save[i] = check;
	}
	for (i = 0; i < x; i++) {
		if (save[i] == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
}