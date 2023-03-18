#include <bits/stdc++.h>
using namespace std;

typedef long long long_t;

long_t fun(long_t n) {
    if (n == 0)
        return 1;
    else {
        long_t s = 0;
        s += 8*fun(n/4);
        return s;
    }
}

int main() {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}
//2-1,2,3은 내가 직접 식을 노트에다가 풀어서 일반화된 식을 작성했다면 이 문제는 fun함수를 변형하여 시간초과에 걸리지 않게 함
//이런식으로 푸는게 정답인듯
