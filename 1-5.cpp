#include <bits/stdc++.h>
using namespace std;

void binsearch(int n, vector<int> S, int x, int& location){
    int low, high, mid;
    low=1; high=n;
    location=0;
    while(low<=high&&location==0){
        mid=(low+high)/2;
        if(x==S[mid])
            location = mid;
        else if(x<S[mid])
            high=mid-1;
        else
            low=mid+1;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> S(n+1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);
    sort(S.begin() + 1, S.end());
    while (m--) {
        int x, location;
        scanf("%d", &x);
        binsearch(n, S, x, location);
        if (location > 0)
            printf("%d is in %d.\n", x, location);
        else
            printf("%d is not in S.\n", x);
    }
}