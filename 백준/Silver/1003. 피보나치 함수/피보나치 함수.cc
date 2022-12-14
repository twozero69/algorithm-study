#include <iostream>
using namespace std;

int zero[41];
int one[41];
int T;

int DP(int n, int* arr) {
    if (n < 3 || arr[n])
        return arr[n];

    return arr[n] = DP(n - 2, arr) + DP(n - 1, arr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    zero[0] = 1;
    zero[1] = 0;
    zero[2] = 1;
    one[0] = 0;
    one[1] = 1;
    one[2] = 1;

    cin >> T;
    int num;
    for (int i = 0; i < T; i++) {
        cin >> num;
        cout << DP(num, zero) << ' ' << DP(num, one) << '\n';
    }
    return 0;
}