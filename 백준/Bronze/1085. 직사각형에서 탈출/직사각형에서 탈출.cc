#include <iostream>
using namespace std;

int x, y, w, h;

int main() {
	cin >> x >> y >> w >> h;
	int tmpx = x < w - x ? x : w - x;
	int tmpy = y < h - y ? y : h - y;
	int _min = tmpx < tmpy ? tmpx : tmpy;
	cout << _min;
	return 0;
}