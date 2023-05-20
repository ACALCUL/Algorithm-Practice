#include <iostream>
#include <vector>
using namespace std;

vector<int> w;//subset의 weight를 기록한 배열
vector<bool> include;//subset이 포함되었는지를 기록한 배열
int n;//subset의 개수
int W;//목표로 하는 가중치
int count=0;//가능한 모든 subset의 개수를 담을 공간

bool promising(int i, int weight, int total){
    return (weight+total>=W)&&(weight==W||weight+w[i+1]<=W);
}

//가능한 모든 subset를 출력하는 함수
void sum_of_subsets(int i, int weight, int total){
    if(promising(i, weight, total)){
        if(weight==W){
            bool whitespace=false;//줄끝공백 제거를 위한 변수
            for(int j=1; j<=n; j++){
                if(include[j]){
                    if(whitespace){
                        cout<<" "<<w[j];
                    }
                    else{
                        cout<<w[j];
                        whitespace=true;
                    }
                    
                }
            }
            cout<<endl;
        }
        else{
            include[i+1]=true;
            sum_of_subsets(i+1, weight+w[i+1], total-w[i+1]);
            include[i+1]=false;
            sum_of_subsets(i+1, weight, total-w[i+1]);
        }
    }
}

//가능한 모든 subset의 개수를 count하는 함수
void sum_of_subsets_count(int i, int weight, int total){
    if(promising(i, weight, total)){
        if(weight==W) count++;
        else{
            include[i+1]=true;
            sum_of_subsets_count(i+1, weight+w[i+1], total-w[i+1]);
            include[i+1]=false;
            sum_of_subsets_count(i+1, weight, total-w[i+1]);
        }
    }
}

int main(){
    cin>>n>>W;
    w.resize(n+1);
    include.resize(n+1);
    int total=0;
    for(int i=1; i<=n; i++){
        cin >> w[i];
        total+=w[i];
    }
    sum_of_subsets_count(0, 0, total);
    cout<<count<<endl;
    sum_of_subsets(0, 0, total);

    return 0;
}