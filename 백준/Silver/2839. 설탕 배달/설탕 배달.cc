#include <iostream>
using namespace std;
int main() {
	int b, n = 0;
	cin >> b;

	while (true) {
		if(b==12){
			cout << n + 4;
			break;
		}
		else if (b == 9) {
			cout << n + 3;
			break;
		}
		else if (b == 6) {
			cout << n + 2;
			break;
		}
		else if (b == 3) {
			cout << n + 1;
			break;
		}
		else if (b == 0) {
			cout << n;
			break;
		}
		else if (b < 0) {
			cout << "-1";
			break;
		}
		b -= 5;
		n++;
	}
}
