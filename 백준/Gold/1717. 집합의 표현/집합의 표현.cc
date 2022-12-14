#include <iostream>
using namespace std;

int parent[1000001];
int N, M;

int findParent(int num) {
	int term = num;
	while (term != parent[term]) {
		term = parent[term];
	}

	parent[num] = term;
	return term;
}

void op1(int a, int b) {
	parent[findParent(a)] = findParent(b);
}

void op2(int a, int b) {
	if (findParent(a) == findParent(b))
		cout << "YES\n" ;
	else
		cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 1000001; i++) {
		parent[i] = i;
	}
	
	cin >> N >> M;
	int op, a, b;
	for (int i = 0; i < M; i++) {
		cin >> op >> a >> b;
		switch (op) {
		case 0:
			op1(a, b);
			break;
		case 1:
			op2(a, b);
			break;
		}
	}

	return 0;
}