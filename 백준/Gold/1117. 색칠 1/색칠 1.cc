#include <iostream>
using namespace std;

long long int W, H, f, c, x1_, x2_, y2_, y1_;

void swap(long long int& fin2, long long int& finx) {
	if (fin2 < finx)
		return;
	else {
		long long int term = fin2;
		fin2 = finx;
		finx = fin2;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> W >> H >> f >> c >> x1_ >> y1_ >> x2_ >> y2_;
	//1. x축으로 접기
	long long int fin2 = W - f;
	long long int finx = f;
	swap(fin2, finx);
	
	//2. y축으로 접기
	long long int weight = c + 1;
	long long int county = y2_ - y1_;

	//3. 페인트 칠하기
	long long int result = -1;
	if (x2_ <= fin2) {
		int countx = x2_ - x1_;
		result = countx * county * weight * 2;
	}
	else if (x1_ < fin2 && fin2 < x2_) {
		long long int count1x = x2_ - fin2;
		long long int count2x = fin2 - x1_;
		result = count1x * county * weight;
		result += count2x * county * weight * 2;
	}
	else if (fin2 <= x1_) {
		long long int countx = x2_ - x1_;
		result = countx * county * weight;
	}
	
	//출력
	cout << W * H - result;
	return 0;
}