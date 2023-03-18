#include <bits/stdc++.h>
using namespace std;

int sum(int n, vector<int> S){
    index i;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    printf("%d", sum(n, S));
}