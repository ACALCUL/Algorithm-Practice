#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;//n개의 queen을 n x n 체스판에 배치
vector<int> col;//n개의 queen을 넣는 경우를 저장하는 배열
long long max_sum=0;//col배열의 값을 숫자의 문자열로 취급했을 때 최댓값 출력
int count_cases=0;//되는 경우의 수를 기록

bool promising(int i){
    int k=1;
    bool flag=true;

    while(k<i && flag){
        if((col[i]==col[k])||(abs(col[i]-col[k])==i-k))
            flag=false;
        k++;
    }
    return flag;
}

void queens(int i){
    int j;
    if(promising(i)){
        if(i==n){
            string max_sum_string="";
            for(j=1; j<=n; j++){
                max_sum_string+= to_string(col[j]);
            }
            //cout<<"max_sum_string: "<<max_sum_string<<endl;
            long long now_max_sum=stoll(max_sum_string);
            if(now_max_sum>max_sum){
                max_sum=now_max_sum;
            }
            count_cases++;
        }
        else
            for(j=1; j<=n; j++){
                col[i+1]=j;
                queens(i+1);
            }
        
    }
}

int main(){
    cin>>n;
    col.resize(n+1, 0);
    queens(0);
    cout<<count_cases<<endl<<max_sum;
    return 0;
}