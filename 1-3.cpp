#include <bits/stdc++.h>
using namespace std;

void exchange(int n, vector<int>& S){
    int i, j, temp;
    for(i=1;i<=n;i++)
        for(j=i+1; j<=n; j++)
            if(S[j]<S[i]){
                temp=S[i];
                S[i]=S[j];
                S[j]=temp;
            }
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    exchange(n, S);
    for (int i = 1; i <= n; i++)
        if (i < n)
            printf("%d ", S[i]);
        else
            printf("%d\n", S[i]);
}