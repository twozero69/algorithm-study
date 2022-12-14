#include <iostream>
using namespace std;

int main() {
	short earth, sun, moon;
	int year = 0;
	scanf("%hd %hd %hd", &earth, &sun, &moon);
	earth--;
	sun--;
	moon--;

	while (1) {
		if (year % 15 == earth)
			if (year % 28 == sun)
				if (year % 19 == moon) {
					printf("%d", year + 1);
					break;
				}
		year++;
	}
}