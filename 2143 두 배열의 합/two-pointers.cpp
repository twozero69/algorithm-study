#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T, N, M;
int arrA[1001];
int arrB[1001];
vector<int> subA, subB;
long result = 0;

void input() {
	cin >> T >> N;
	for (int i = 0; i < N; i++) {
		cin >> arrA[i];
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> arrB[i];
	}
}

void makeSub(int* arr, int arrSize, vector<int>& sub) {
	for (int i = 0; i < arrSize; i++) {
		int sum = 0;
		for (int j = i; j < arrSize; j++) {
			sum += arr[j];
			sub.push_back(sum);
		}
	}
}

bool desc(int a, int b) {
	return a > b;
}

void findPairFromSub() {
	int pointerA = 0, pointerB = 0;

	while (pointerA < subA.size() && pointerB < subB.size()) {
		int sum = subA[pointerA] + subB[pointerB];
		if (sum == T) {
			int valueA = subA[pointerA];
			int valueB = subB[pointerB];
			
			int cntA = 0;
			for (int i = pointerA; i < subA.size(); i++) {
				if (valueA != subA[i])
					break;

				cntA++;
			}

			int cntB = 0;
			for (int i = pointerB; i < subB.size(); i++) {
				if (valueB != subB[i])
					break;

				cntB++;
			}

			result += (long)cntA * (long)cntB;
			pointerA += cntA;
			pointerB += cntB;
		}
		else if (sum > T) {
			pointerB++;
		}
		else {
			pointerA++;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();
	makeSub(arrA, N, subA);
	makeSub(arrB, M, subB);
	sort(subA.begin(), subA.end());
	sort(subB.begin(), subB.end(), desc);
	findPairFromSub();
	cout << result;
	return 0;
}