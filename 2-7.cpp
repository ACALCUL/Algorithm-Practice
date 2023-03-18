#include <bits/stdc++.h>
using namespace std;

int cnt=0;
    int move_cnt=0;
void hanoi(int n, int k, char src, char via, char dst) {
    cnt++;
    if (n == 1) {
        if(++move_cnt==k)
            printf("%c -> %c\n", src, dst);
    }
    else {
        hanoi(n-1, k, src, dst, via);
        hanoi(1, k, src, via, dst);
        hanoi(n-1, k, via, src, dst);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    hanoi(n, k , 'A', 'B', 'C');
    printf("%d", cnt);
}