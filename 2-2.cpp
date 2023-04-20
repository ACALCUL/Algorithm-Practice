#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;

typedef long long long_t;

int main() {
    long_t n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    cout << ((n+1)/2)*floor((log(4*m))/log(2))*floor(log(8*p)/log(2))<<endl;
}