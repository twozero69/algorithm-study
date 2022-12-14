#include <iostream>
using namespace std;

int K = 0;    //0~1000 스위치를 누르는 횟수
int N = 0;    //1~50   행
int M = 0;    //1~50   열

char arr[50][50] = { {'0',}, };
int MAX = 0;
bool check[50] = { false, };

void checkRow(bool odd) {   //odd홀수여부
    for (int i = 0; i < N; i++) {
        if (!check) {
            continue;
        }
        else {
            int count = 0;
            count++;
            check[i] = true;
            for (int a = i + 1; a < N; a++) {
                bool flag = true;
                for (int b = 0; b < M; b++) {
                    if (arr[i][b] != arr[a][b]) {
                        flag = false;
                        break;
                    }
                }

                if (flag) {
                    check[a] = true;
                    count++;
                }
            }

            int countZero = 0;
            for (int j = 0; j < M; j++) {
                if (arr[i][j] == '0')
                    countZero++;
            }

            if (K < countZero)  //스위치 횟수가 0의 개수보다 작으면 패스
                continue;

            if (odd) {  //K가 홀수일 때
                if (countZero % 2 == 0)  //0의 개수가 짝수
                    continue;
            }
            else {  //K가 짝수일 때
                if (countZero % 2 == 1) //0의 개수가 홀수
                    continue;
            }

            MAX = MAX > count ? MAX : count;
        }
    }
}
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;

    for (int i = 0; i < N; i++) {   //N은 행
        for (int j = 0; j < M; j++) {   //M은 열
            cin >> arr[i][j]; //1은 켜져있는 상태, 0은 꺼져있는 상태
        }
    }
    cin >> K;
    
    if (K % 2 == 1)
        checkRow(true);
    else
        checkRow(false);

    cout << MAX;
    return 0;
}