//knapsack2로는 11-1을 못풉니다..
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;//n: 아이템의 개수

vector<int> p, w;
//p: 각 아이템에 대한 profit
//w: 각 아이템에 대한 weight

typedef struct item *item_ptr;
typedef struct item{
    int id;
    int weight;
    int profit;
    int profit_per_unit;
}item_t;

vector<item_t> items;

struct compare_item{
    bool operator()(item_t i, item_t j){
    if(i.profit_per_unit<j.profit_per_unit)
        return true;
    return false;
    }
};

int knapsack2(vector<vector<int>> &P, int W){
    for(int i=0; i<=n; i++)
        P[i][0]=0;
    for(int j=1; j<=W; j++)
        P[0][j]=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=W; j++){
            P[i][j]=(w[i]>j)?P[i-1][j]:max(P[i-1][j],p[i]+P[i-1][j-w[i]]);
        }
     
    return P[n][W];
}

int main(){
    cin >> n;
    items.resize(n+1);
    for(int i=1; i<=n; i++){
        items[i].id=i;
        cin >> items[i].weight;
    }
    for(int i=1; i<=n; i++){
        cin >> items[i].profit;
        items[i].profit_per_unit=items[i].profit/items[i].weight;
        //원래는 float형이 맞으나 문제 조건에 따라 int형 나눗셈 수행
    }

    //PQ를 통해 items를 정렬하기
    priority_queue<item, vector<item>, compare_item> pq;
    for(int i=1; i<=n; i++){
        pq.push(items[i]);
    }

    for(int i=1; i<=n;i++){
        items[i]=pq.top();
        pq.pop();
    }

    p.resize(n+1);
    w.resize(n+1);
    for(int i=1; i<=n; i++){
        p[i]=items[i].profit;
        w[i]=items[i].weight;
    }

    int W_num;
    //W_num: 주어진 배낭 무게의 개수
    vector<int> W;
    //W: 주어진 배낭 무게
    int W_max=0;
    cin>>W_num;
    W.resize(W_num, 0);
    for(int i=0; i<W_num; i++){
        cin>>W[i];
        if(W_max<W[i]){
            W_max=W[i];
        }
    }

    vector<vector<int>> P;
    P.resize(n+1, vector<int>(W_max+1, 0));
    //resize를 반복문안에 넣으면 오류 발생(resize의 한계점 때문)
    for(int i=0; i<W_num; i++){
        cout<<knapsack2(P, W[i])<<endl;

        for(int k=1; k<=n; k++)
            for(int j=1; j<=W[i]; j++){
                if(P[k][j] != 0){
                    cout<<k<<" "<<j<<" "<<P[k][j]<<endl;
                }
            }

        /* for(int j=1; j<=n; j++){
            cout<<P[j][1];
            for(int k=2; k<=W[i]; k++)
                cout<<" "<<P[j][k];
            cout<<endl;
        }  */    
    }
}