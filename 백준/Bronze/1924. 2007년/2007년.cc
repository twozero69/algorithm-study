#include <stdio.h>

int main() {
	int month, date;
	int sum;
	int yoil;
	scanf("%d %d", &month, &date);

	switch (month) {
	case 1: sum = 0; break;
	case 2: sum = (31 * 1); break;
	case 3: sum = (31 * 1) + 28; break;
	case 4: sum = (31 * 2) + 28; break;
	case 5: sum = (31 * 2) + (30 * 1) + 28; break;
	case 6: sum = (31 * 3) + (30 * 1) + 28; break;
	case 7: sum = (31 * 3) + (30 * 2) + 28; break;
	case 8: sum = (31 * 4) + (30 * 2) + 28; break;
	case 9: sum = (31 * 5) + (30 * 2) + 28; break;
	case 10: sum = (31 * 5) + (30 * 3) + 28; break;
	case 11: sum = (31 * 6) + (30 * 3) + 28; break;
	case 12: sum = (31 * 6) + (30 * 4) + 28; break;
	}
	sum += date;
	yoil = sum % 7;
	switch (yoil) {
	case 0: printf("SUN"); break;
	case 1: printf("MON"); break;
	case 2: printf("TUE"); break;
	case 3: printf("WED"); break;
	case 4: printf("THU"); break;
	case 5: printf("FRI"); break;
	case 6: printf("SAT"); break;
	}
	return 0;
}