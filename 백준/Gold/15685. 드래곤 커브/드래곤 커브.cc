#include <iostream>
#include <vector>
using namespace std;

int N;

bool map[101][101];
int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };

void print(int size) {
	for (int i = 0; i <= size; i++) {
		for (int j = 0; j <= size; j++) {
			cout << map[i][j];
		}
		cout << '\n';
	}
	cout << '\n';
}


pair<int, int> rotate_point(pair<int, int>& input, pair<int, int>& base) {
	pair<int, int> output;

	//y
	output.first = base.first + input.second - base.second;

	//x
	output.second = base.second + base.first - input.first;

	//draw
	if (output.first >= 0 && output.first <= 100 && output.second >= 0 && output.second <= 100)
		map[output.first][output.second] = true;

	return output;
}


void draw_dragon(int row, int col, int dir, int gen) {
	vector<pair<int, int>> v;
	map[row][col] = true;
	map[row + dy[dir]][col + dx[dir]] = true;
	v.push_back(make_pair(row, col));
	v.push_back(make_pair(row + dy[dir], col + dx[dir]));

	pair<int, int> base = v.back();
	for (int i = 1; i <= gen; i++) {
		int size = v.size() - 1;
		for (int i = 1; i < size; i++) {
			v.push_back(rotate_point(v[i], base));
		}

		v.push_back(rotate_point(v[0], base));
		base = v.back();
		//print(6);
	}
}

int get_result() {
	int result = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] && map[i + 1][j] && map[i][j + 1] && map[i + 1][j + 1])
				result++;
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	int x, y, d, g;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		draw_dragon(y, x, d, g);
	}

	cout << get_result();
	return 0;
}