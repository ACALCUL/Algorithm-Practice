#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;//n: 아이템의 개수
int W;//W: 베낭의 무게

vector<int> p, w;
//p: 각 아이템에 대한 profit
//w: 각 아이템에 대한 weight

vector<int> include;
int maxprofit=0;
float bound;

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

queue<int> Q;
//maxprofit 값일 떄의 weight와 profit 저장

bool promising(int i, int profit, int weight){
    int j, k, totweight;
    if(weight >=W){
        cout<<i<<" "<<weight<<" "<<profit<<" "<<bound<<" "<<maxprofit<<endl;
        return false;
    }
    else{
        j=i+1;
        bound=profit;
        totweight=weight;
        while(j<=n&&totweight+w[j]<=W){
            totweight+=w[j];
            bound+=p[j];
            j++;
        }
        k=j;
        if(k<=n)
            bound+=(W-totweight)*((float)p[k]/w[k]);
        cout<<i<<" "<<weight<<" "<<profit<<" "<<bound<<" "<<maxprofit<<endl;
        return bound>maxprofit;
    }
    
}

void knapsack4(int i, int profit, int weight){
    if(weight <= W && profit >maxprofit){
        maxprofit=profit;
        while (!Q.empty()) {
            Q.pop();
        }
        for(int j=1; j<=n; j++){
        if(include[j]){
            Q.push(w[j]);
            Q.push(p[j]);
        }
    }
    }
    if(promising(i, profit, weight)){
        include[i+1]=true;
        knapsack4(i+1, profit+p[i+1], weight+w[i+1]);
        include[i+1]=false;
        knapsack4(i+1, profit, weight);
    }
}

int main(){
    cin >> n>>W;
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

    include.resize(n+1);

    knapsack4(0, 0, 0);
    cout<<maxprofit<<endl;
    while (!Q.empty()) {
        cout << Q.front() << " ";
        Q.pop();
        cout<<Q.front()<<endl;
        Q.pop();
    }
}