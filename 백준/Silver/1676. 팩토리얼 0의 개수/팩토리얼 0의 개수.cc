#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    int two = 0, five = 0;
    cin >> n;
    
    for (int i = 2; i <= n; i = i * 2)
        two += n / i;
    for (int i = 5; i <= n; i = i * 5)
        five += n / i;
 
    cout << min(two, five);
    return 0;
}