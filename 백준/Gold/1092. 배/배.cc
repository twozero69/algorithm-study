#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N = 0;
int M = 0;

vector<int> crain, box;

int main() {
	cin >> N;
	int term;
	for (int i = 0; i < N; i++) {
		cin >> term;
		crain.push_back(term);
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> term;
		box.push_back(term);
	}

	sort(crain.begin(), crain.end());
	sort(box.begin(), box.end());

	if (crain[N - 1] < box[M - 1]) {
		cout << "-1";
		return 0;
	}

	int minute = 0;
	int crainMax = N - 1;
	while (!box.empty()) {
		minute++;
		int index = crainMax;
		for (int i = box.size()-1; i >= 0; i--) {
			if (crain[index] >= box[i]) {
				box.erase(box.begin() + i);
				index--;
				if (index < 0)
					break;
			}
		}
	}

	cout << minute;

	return 0;
}