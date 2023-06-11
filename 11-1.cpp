#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

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

int knapsack3(int n, int W, vector<int> w, vector<int> p, map<pair<int, int>, int> &P) {
    if(n==0||W<=0)
        return 0;
    int lvalue=(P.find(make_pair(n-1,W)) != P.end())
                ?P[make_pair(n-1, W)]
                :knapsack3(n-1, W, w, p, P);
    //find함수는 키의 값을 반환해주는데, 키가 map에 존재하지 않을 시 P.end를 출력함
    //만약 키가 있으면 키의 값을 반환하고, 키가 없으면 키를 만든다.
    int rvalue=(P.find(make_pair(n-1, W-w[n]))!=P.end())
                ?P[make_pair(n-1, W-w[n])]
                :knapsack3(n-1, W-w[n], w, p, P);
    P[make_pair(n,W)]=(w[n]>W)?lvalue:max(lvalue, p[n]+rvalue);
    return P[make_pair(n, W)];
}

int main(){
    int n;//n: 아이템의 개수
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

    vector<int> p, w;
    //p: 각 아이템에 대한 profit
    //w: 각 아이템에 대한 weight
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
    cin>>W_num;
    W.resize(W_num, 0);
    for(int i=0; i<W_num; i++){
        cin>>W[i];
    }

    
    for(int i=0; i<W_num; i++){
        map<pair<int, int>, int> P;
        cout<<knapsack3(n, W[i], w, p, P)<<endl;
        for (auto element : P) {
        auto key = element.first;
        auto value = element.second;
        cout << key.first << " "<<key.second <<" "<< value <<endl;
        }
    }

}




