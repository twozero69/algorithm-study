#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int maxRow = 3;
int maxCol = 3;
int arr[101][101] = { {0,}, };
int r, c, k;
int result = 0;
typedef struct numInfo {
	int num;
	int cnt;
}NUMINFO;

void printArr() {
	for (int i = 1; i <= maxRow; i++) {
		for (int j = 1; j <= maxCol; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << result << "s, maxRow=" << maxRow << ", maxCol=" << maxCol << "\n\n";
}

bool compare(NUMINFO A, NUMINFO B) {
	if (A.cnt != B.cnt)
		return A.cnt < B.cnt;

	return A.num < B.num;
}

void operationR() {
	int newMaxCol = 0;
	for (int row = 1; row <= maxRow; row++) {
		//컨테이너 생성
		int cnt[101];
		for (int i = 1; i <= 100; i++) {
			cnt[i] = 0;
		}

		//숫자세기
		for (int col = 1; col <= maxCol; col++) {
			int num = arr[row][col];
			if (num == 0)
				continue;

			cnt[num]++;
		}

		vector<NUMINFO> numInfos;
		for (int i = 1; i <= 100; i++) {
			if (cnt[i] == 0)
				continue;

			NUMINFO term;
			term.num = i;
			term.cnt = cnt[i];
			numInfos.push_back(term);
		}

		//정렬
		sort(numInfos.begin(), numInfos.end(), compare);

		vector<int> newCol;
		for (int i = 0; i < numInfos.size(); i++) {
			newCol.push_back(numInfos[i].num);
			newCol.push_back(numInfos[i].cnt);
		}

		int newColSize = newCol.size();
		if (newColSize > 100)
			newColSize = 100;

		newMaxCol = newMaxCol > newColSize ? newMaxCol : newColSize;

		for (int col = 1; col <= 100; col++) {
			if (col <= newColSize) {
				arr[row][col] = newCol[col - 1];
			}
			else {
				arr[row][col] = 0;
			}
		}

	}

	maxCol = newMaxCol;
}

void operationC() {
	int newMaxRow = 0;
	for (int col = 1; col <= maxCol; col++) {
		//컨테이너 생성
		int cnt[101];
		for (int i = 1; i <= 100; i++) {
			cnt[i] = 0;
		}

		//숫자세기
		for (int row = 1; row <= maxRow; row++) {
			int num = arr[row][col];
			if (num == 0)
				continue;

			cnt[num]++;
		}

		vector<NUMINFO> numInfos;
		for (int i = 1; i <= 100; i++) {
			if (cnt[i] == 0)
				continue;

			NUMINFO term;
			term.num = i;
			term.cnt = cnt[i];
			numInfos.push_back(term);
		}

		//정렬
		sort(numInfos.begin(), numInfos.end(), compare);

		vector<int> newRow;
		for (int i = 0; i < numInfos.size(); i++) {
			newRow.push_back(numInfos[i].num);
			newRow.push_back(numInfos[i].cnt);
		}

		int newRowSize = newRow.size();
		if (newRowSize > 100)
			newRowSize = 100;

		newMaxRow = newMaxRow > newRowSize ? newMaxRow : newRowSize;

		for (int row = 1; row <= 100; row++) {
			if (row <= newRowSize) {
				arr[row][col] = newRow[row - 1];
			}
			else {
				arr[row][col] = 0;
			}
		}

	}

	maxRow = newMaxRow;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arr[i][j];
		}
	}

	while (true) {
		if (arr[r][c] == k)
			break;

		if (result > 100)
			break;

		//printArr();

		if (maxRow >= maxCol)
			operationR();
		else
			operationC();

		result++;
	}

	if (result > 100)
		cout << -1;
	else
		cout << result;
	return 0;
}