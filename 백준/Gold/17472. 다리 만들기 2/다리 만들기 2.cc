#include <iostream>
#include <vector>
#include <string.h>		//memset
using namespace std;

int N, M;	//N은 행 M은 열
int _array[11][11];	//1~10의 인덱스 사용
int termarray[11][11];
bool check[11][11];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int landcount;
int bridge[7][7];		//2개의 인덱스는 연결된 2개의 섬을 의미하고 다리의 길이를 기록함.
int bridgenum[7];
vector<pair<int, pair<int, int>>> bridges;
vector<pair<int, pair<int, int>>> absolutebridges;
bool checkbridges[100];
int term2[7][20];
int term2size[7];
bool checksimulation[7];
int result;
int finalresult = 2147483647;

void printarray(int array[][11]) {
	cout << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << array[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

void printbridge() {
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			cout << bridge[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
	for (int k = 1; k <= 6; k++) {
		cout << bridgenum[k] << ' ';
	}
	cout << '\n'<<'\n';
}

void printbridges() {
	cout << bridges.size() << '\n';
	for (int i = 0; i < bridges.size(); i++) {
		cout << bridges[i].first << ' ' << bridges[i].second.first << ' ' << bridges[i].second.second << '\n';
	}
	cout << '\n';
}

void printabsolutebridges() {
	cout << absolutebridges.size() << '\n';
	for (int i = 0; i < absolutebridges.size(); i++) {
		cout << absolutebridges[i].first << ' ' << absolutebridges[i].second.first << ' ' << absolutebridges[i].second.second << '\n';
	}
	cout << '\n';
}

void landdfs(int a, int b) {		//1~6의 숫자로 섬을 표현
	if (check[a][b] || !_array[a][b])
		return;

	check[a][b] = true;
	termarray[a][b] = landcount;

	int newx, newy;
	for (int i = 0; i < 4; i++) {
		newx = b + dx[i];
		newy = a + dy[i];

		if (newx<1 || newy<1 || newx>M || newy>N)
			continue;

		landdfs(newy, newx);
	}
}

void searchland() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (_array[i][j] == 1) {
				if (!check[i][j]) {
					landcount++;
					landdfs(i, j);
				}
			}
		}
	}
}

void searchbridge() {
	for (int i = 1; i <= N; i++) {		//가로방향 다리 탐색
		int term = 0;
		int dist = 0;
		for (int j = 1; j <= M; j++) {
			if (_array[i][j]) {
				switch (dist) {
				case 0:
				case 1:
					term = j;
					dist = 0;
					break;
				default:			//거리가 2이상인 경우
					int a, b;
					a = termarray[i][term];
					b = termarray[i][j];

					if (!bridge[a][b] || (bridge[a][b] && bridge[a][b] > dist)) {
						bridge[a][b] = dist;
						bridge[b][a] = dist;
					}

					dist = 0;
					term = j;
					break;
				}
			}
			else {
				if (term)
					dist++;
			}
		}
	}

	for (int j = 1; j <= M; j++) {
		int term = 0;
		int dist = 0;
		for (int i = 1; i <= N; i++) {		//세로방향 다리 탐색
			if (_array[i][j]) {
				switch (dist) {
				case 0:
				case 1:
					term = i;
					dist = 0;
					break;
				default:			//거리가 2이상인 경우
					int a, b;
					a = termarray[term][j];
					b = termarray[i][j];

					if (!bridge[a][b] || (bridge[a][b] && bridge[a][b] > dist)) {
						bridge[a][b] = dist;
						bridge[b][a] = dist;
					}

					dist = 0;
					term = i;
					break;
				}
			}
			else {
				if (term)
					dist++;
			}
		}
	}

	for (int i = 1; i <= landcount; i++) {
		for (int j = 1; j <= landcount; j++) {
			if (bridge[i][j])
				bridgenum[i]++;
		}
	}
}

void arrangebridge() {
	for (int i = 1; i <= landcount; i++) {
		if (bridgenum[i] == 1) {
			for (int j = 1; j <= landcount; j++) {
				if (bridge[i][j]) {
					absolutebridges.push_back(make_pair(bridge[i][j], make_pair(i, j)));
					bridge[i][j] = 0;
					bridge[j][i] = 0;
				}
			}
		}
	}

	for (int i = 1; i <= landcount; i++) {
		if(bridgenum[i]>=2) {
			for (int j = i; j <= landcount; j++) {
				if (bridge[i][j]) {
					bridges.push_back(make_pair(bridge[i][j], make_pair(i, j)));
				}
			}
		}
	}
}

void simulationdfs(int idx) {
	if (checksimulation[idx])
		return;

	checksimulation[idx] = true;

	for (int i = 0; i < term2size[idx]; i++) {
		simulationdfs(term2[idx][i]);
	}
}

void simulation() {
	result = 0;
	memset(checksimulation, false, sizeof(bool) * 7);
	memset(term2size, 0, sizeof(int) * 7);
	memset(term2, 0, sizeof(int) * 7 * 20);

	for (int i = 0; i < absolutebridges.size(); i++) {
		result += absolutebridges[i].first;
		term2[absolutebridges[i].second.first][term2size[absolutebridges[i].second.first]] = absolutebridges[i].second.second;
		term2[absolutebridges[i].second.second][term2size[absolutebridges[i].second.second]] = absolutebridges[i].second.first;
		term2size[absolutebridges[i].second.first]++;
		term2size[absolutebridges[i].second.second]++;
	}

	for (int i = 0; i < bridges.size(); i++) {
		if (checkbridges[i]) {
			result += bridges[i].first;
			term2[bridges[i].second.first][term2size[bridges[i].second.first]] = bridges[i].second.second;
			term2[bridges[i].second.second][term2size[bridges[i].second.second]] = bridges[i].second.first;
			term2size[bridges[i].second.first]++;
			term2size[bridges[i].second.second]++;
		}
	}

	simulationdfs(1);
}

void checking() {
	for (int i = 1; i <= landcount; i++) {
		if (!checksimulation[i])
			return;
	}

	finalresult = finalresult > result ? result : finalresult;
}

void maindfs(int idx) {
	simulation();
	checking();

	for (int i = idx; i < bridges.size(); i++) {
		checkbridges[i] = true;
		maindfs(idx + 1);
		checkbridges[i] = false;	
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> _array[i][j];
		}
	}

	searchland();
	searchbridge();
	arrangebridge();
	maindfs(0);

	if (finalresult == 2147483647)
		cout << -1;
	else
		cout << finalresult;
}