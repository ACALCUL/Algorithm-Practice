#include <iostream>
#include <vector>
using namespace std;

int cnt=0;
vector<vector<int>> DP;

int bin(int n, int k)
{
    cnt++; // 함수 호출 횟수 카운트
    if (k==0 || k==n )
        DP[n][k] = 1;
    else if (!(DP[n][k]))
        DP[n][k] = (bin(n-1, k) + bin(n-1, k-1)) % 10007; // memoize using recursive call
    
    return DP[n][k]; // return memoized value
}

int main(){
    int n, k;
    cin >> n >> k;
    // 0 <= k <= n <= 1000
    DP.resize(n+1, vector<int>(n+1, 0));//n아 아니라 n+1까지 resize해야함에 주의
    int result=bin(n,k);
    cout << result << endl << cnt;
    return 0;
}
