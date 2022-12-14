#include <iostream>
using namespace std;


char cube[54];

char cube_save[54] = {
	'w','w','w','w','w','w','w','w','w',
	'y','y','y','y','y','y','y','y','y',
	'r','r','r','r','r','r','r','r','r',
	'o','o','o','o','o','o','o','o','o',
	'g','g','g','g','g','g','g','g','g',
	'b','b','b','b','b','b','b','b','b'
};


int rotation[6][12] = {
	{33,34,35,45,48,51,20,19,18,44,41,38},
	{29,28,27,36,39,42,24,25,26,53,50,47},
	{6,7,8,51,52,53,15,16,17,42,43,44},
	{2,1,0,38,37,36,11,10,9,47,46,45},
	{0,3,6,18,21,24,17,14,11,27,30,33},
	{8,5,2,35,32,29,9,12,15,26,23,20}
};


void rotate_top(int idx) {
	int start_idx = idx * 9;
	char term[9];
	for (int i = 0; i < 9; i++) {
		term[i] = cube[start_idx + i];
	}

	cube[start_idx] = term[6];
	cube[start_idx + 1] = term[3];
	cube[start_idx + 2] = term[0];
	cube[start_idx + 3] = term[7];
	cube[start_idx + 4] = term[4];
	cube[start_idx + 5] = term[1];
	cube[start_idx + 6] = term[8];
	cube[start_idx + 7] = term[5];
	cube[start_idx + 8] = term[2];
}


void rotate_side(int idx) {
	char term[12];
	for (int i = 0; i < 12; i++) {
		term[i] = cube[rotation[idx][i]];
	}

	for (int i = 0; i < 12; i++) {
		cube[rotation[idx][i]] = term[(i + 9) % 12];
	}
}


void rotate_cube(char ori) {
	switch (ori) {
	case 'U':
		rotate_top(0);
		rotate_side(0);
		break;
	case 'D':
		rotate_top(1);
		rotate_side(1);
		break;
	case 'F':
		rotate_top(2);
		rotate_side(2);
		break;
	case 'B':
		rotate_top(3);
		rotate_side(3);
		break;
	case 'L':
		rotate_top(4);
		rotate_side(4);
		break;
	case 'R':
		rotate_top(5);
		rotate_side(5);
		break;
	}
}


void reset_cube() {
	for (int i = 0; i < 54; i++) {
		cube[i] = cube_save[i];
	}
}


void print_cube() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << cube[3 * i + j];
		}
		cout << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		reset_cube();
		int M;
		cin >> M;
		char ori, dir;
		for (int j = 0; j < M; j++) {
			cin >> ori >> dir;
			int cnt;
			if (dir == '+')
				cnt = 1;
			else if (dir == '-')
				cnt = 3;

			for (int i = 0; i < cnt; i++)
				rotate_cube(ori);
		}

		print_cube();
	}

	return 0;
}