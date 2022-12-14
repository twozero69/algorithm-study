#include <iostream>
#include <math.h>
#include <memory.h>
using namespace std;
#define INT_MAX 2147483647

int N = 0;
int M = 0;
string str;
bool check[10];
int result = INT_MAX;
int _select[6] = { 0, };

void calcResult(int term, int count) {
	int tmp = abs(N - term) + count;
	result = result < tmp ? result : tmp;
}

void bruteforce(int count) {
	if (str.size()==count) {
		int term = 0;
		for (int i = 0; i < count; i++)
			term += _select[i] * pow(10, count - i - 1);
		
		calcResult(term, str.size());
		return;
	}

	for (int i = 0; i < 10; i++) {
		if (!check[i])
			continue;

		_select[count] = i;
		bruteforce(count + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> str;
	for (int i = 0; i < str.size(); i++) {
		str[i] -= 0x30;
		N += str[i] * pow(10, str.size() - i - 1);
	}

	cin >> M;

	memset(check, true, sizeof(check));
	int tmp;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		check[tmp] = false;
	}
	
	//1. 100에서 +,- 버튼으로 이동.
	calcResult(100, 0);
	
	//2. 자리수가 1개 적은 경우
	if (str.size() != 1) {
		int max = -1;
		for (int i = 0; i < 10; i++) {
			if (check[i]) {
				max = max > i ? max : i;
			}
		}

		int term = 0;
		for (int i = 0; i < str.size() - 1; i++)
			term += max * pow(10, i);

		calcResult(term, str.size() - 1);
	}

	//3. 자리수가 1개 많은 경우
	if (str.size() <= 5) {
		int min = INT_MAX;
		for (int i = 0; i < 10; i++) {
			if (check[i]) {
				min = min < i ? min : i;
			}
		}

		int firstMin = INT_MAX;
		int firstLimit = 0;
		if (str.size() == 5)
			firstLimit = 6;
		else
			firstLimit = 10;

		for (int i = 1; i < firstLimit; i++) {
			if (check[i]) {
				firstMin = firstMin < i ? firstMin : i;
			}
		}

		if (firstMin != INT_MAX) {
			int term = 0;
			term += firstMin * pow(10, str.size());
			for (int i = 0; i < str.size(); i++)
				term += min * pow(10, i);

			calcResult(term, str.size() + 1);
		}
	}

	//4. 자리수가 같은 경우
	bruteforce(0);

	//결과출력
	cout << result;
	return 0;
}