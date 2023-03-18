#include <bits/stdc++.h>
using namespace std;
typedef long long long_t;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int K, k, cnt, MAX_cnt;
    long_t seq_num;
    MAX_cnt=0;

    for(k = n; k<=m; k++){
        seq_num=k;
        cnt=0;
        while(seq_num!=1){
        cnt++;
        if(seq_num%2)
            seq_num=3*seq_num+1;
        else
            seq_num/=2;
        }
        //오류 확인용 printf("k: %d, cnt: %d\n", k, cnt);
        if(MAX_cnt<cnt){
            MAX_cnt=cnt;
            K=k;
            }
    }
    
    printf("%d %d\n", K, MAX_cnt);

    printf("%d ", K);
    while(K!=1){
        if(K%2)
            K=3*K+1;
        else
            K=K/2;
        printf("%d ", K);
    }
} 