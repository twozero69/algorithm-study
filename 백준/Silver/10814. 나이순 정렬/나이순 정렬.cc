#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct info {
	int age;
	int idx;
	string name;
};

int N;
vector<info> V;	//first name, second age

bool compare(info a, info b) {
	if (a.age != b.age)
		return a.age < b.age;
	return a.idx < b.idx;
}

int main() {
	cin >> N;
	info tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp.age >> tmp.name;
		tmp.idx = i;
		V.push_back(tmp);
	}

	sort(V.begin(), V.end(), compare);
	for (int i = 0; i < N; i++) {
		cout << V[i].age << ' ' << V[i].name << '\n';
	}
	return 0;
}