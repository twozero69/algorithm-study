#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int wood[1000000];

bool compare(int a, int b) {
	return a > b;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> wood[i];
	}

	sort(wood, wood + N, compare);
	
	int cuttingHeight = wood[0];
	int idx = 0;
	int sum = 0;
	while (cuttingHeight>0) {
		//절단기 높이 낮추기
		cuttingHeight--;
		if (cuttingHeight < wood[idx]) {
			int newIdx = idx;
			for (int i = idx; i < N; i++) {
				if (wood[idx] != wood[i]) {
					break;
				}
				
				newIdx++;
			}

			idx = newIdx;
		}

		//나무자르기
		sum += idx;

		//조건체크
		if (sum >= M)
			break;
	}

	cout << cuttingHeight;
	return 0;
}