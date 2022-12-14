#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int fuel;
int map[21][21];
pair<int, int> goal[21][21];
pair<int, int> taxi;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int cnt = 0;

typedef struct container {
	int row = -1;
	int col = -1;
	int cost = -1;
}CONTAINER;

bool compare(CONTAINER A, CONTAINER B) {
	if (A.cost != B.cost)
		return A.cost < B.cost;
	
	if (A.row != B.row)
		return A.row < B.row;

	return A.col < B.col;
}

CONTAINER findPassenger() {
	bool check[21][21];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			check[i][j] = false;
		}
	}

	queue<CONTAINER> q;
	CONTAINER start;
	start.row = taxi.first;
	start.col = taxi.second;
	start.cost = 0;
	q.push(start);

	vector<CONTAINER> v;

	while (!q.empty()) {
		CONTAINER current = q.front();
		q.pop();
		int row = current.row;
		int col = current.col;
		int cost = current.cost;

		if (row<1 || row>N || col<1 || col>N)
			continue;

		if (check[row][col] || map[row][col] == 1)
			continue;

		check[row][col] = true;

		if (map[row][col] == -1)
			v.push_back(current);

		int newCost = cost + 1;
		for (int i = 0; i < 4; i++) {
			CONTAINER term;
			term.row = row + dy[i];
			term.col = col + dx[i];
			term.cost = newCost;
			q.push(term);
		}
	}

	//더 이상 승객이 없는 경우 || 승객이 도착할 수 없는 위치에 있는 경우
	if (v.empty()) {
		CONTAINER term;
		return term;
	}

	sort(v.begin(), v.end(), compare);
	return v.front();
}

int getMoveCost(pair<int,int> destination) {
	bool check[21][21];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			check[i][j] = false;
		}
	}

	queue<CONTAINER> q;
	CONTAINER start;
	start.row = taxi.first;
	start.col = taxi.second;
	start.cost = 0;
	q.push(start);

	while (!q.empty()) {
		CONTAINER current = q.front();
		q.pop();
		int row = current.row;
		int col = current.col;
		int cost = current.cost;

		if (row<1 || row>N || col<1 || col>N)
			continue;

		if (check[row][col] || map[row][col] == 1)
			continue;

		check[row][col] = true;

		if (row == destination.first && col == destination.second)
			return cost;

		int newCost = cost + 1;
		for (int i = 0; i < 4; i++) {
			CONTAINER term;
			term.row = row + dy[i];
			term.col = col + dx[i];
			term.cost = newCost;
			q.push(term);
		}
	}

	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> fuel;
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	
	cin >> taxi.first >> taxi.second;

	for (int i = 0; i < M; i++) {
		int startRow, startCol, endRow, endCol;
		cin >> startRow >> startCol >> endRow >> endCol;
		map[startRow][startCol] = -1;
		goal[startRow][startCol] = make_pair(endRow, endCol);
	}

	while (true) {
		//가까운 승객 위치 찾기
		CONTAINER nextPassenger = findPassenger();
		int passengerRow = nextPassenger.row;
		int passengerCol = nextPassenger.col;
		int passengerCost = nextPassenger.cost;

		//승객이 도착할 수 없는 위치에 있는 경우
		if (passengerCost == -1) {
			cout << -1;
			return 0;
		}

		//퇴근하는 경우
		if (passengerCost > fuel) {
			cout << -1;
			return 0;
		}

		//승객에게 택시이동하고 태우기
		taxi.first = passengerRow;
		taxi.second = passengerCol;
		fuel -= passengerCost;
		map[passengerRow][passengerCol] = 0;

		//목적지까지의 비용계산
		pair<int, int> destination = goal[nextPassenger.row][nextPassenger.col];
		int moveCost = getMoveCost(destination);

		//목적지가 도착할 수 없는 위치에 있는 경우 || 퇴근하는 경우
		if (moveCost == -1 || moveCost > fuel) {
			cout << -1;
			return 0;
		}

		//도착지까지 이동, 연료 충전
		cnt++;
		taxi = destination;
		fuel += moveCost;

		//더 이상 승객이 없는 경우
		if (cnt == M) {
			cout << fuel;
			return 0;
		}
	}

	return 0;
}