#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct item *item_ptr;
typedef struct item{
    int id;
    int weight;
    int profit;
    int profit_per_unit;
}item_t;

int n, T;
vector<int> W;
vector<item_t> items;
queue<int> Q;
//n, T, W, 그리고 items 는 전역변수로
//n: 아이템 개수, W: 배낭 개수

struct compare_item{
    bool operator()(item_t i, item_t j){
    if(i.profit_per_unit<j.profit_per_unit)
        return true;
    return false;
    }
};

//fractional knapsack을 greedy approach로 구현
void knapsack1(){
    int totweight=0;
    int maxprofit=0;
    for(int j=0; j<T; j++){
        totweight=0, maxprofit=0;
        for(int i=0; i<n; i++){
            if(totweight + items[i].weight<=W[j]){
                Q.push(items[i].weight);
                Q.push(items[i].profit);

                maxprofit += items[i].profit;
                totweight += items[i].weight;
                
                if(totweight==W[j]) break;
                //중요: 딱 맞아떨어지는 경우에는 0, 0을 push할 수 있으므로 break처리
            }
            else{
                Q.push(W[j]-totweight);
                Q.push((W[j]-totweight)*items[i].profit_per_unit);

                maxprofit+=(W[j]-totweight)*items[i].profit_per_unit;
                totweight+=(W[j]-totweight);
                break;
            }
        }
        cout<<maxprofit<<endl;
            while(!Q.empty()){
                    cout<< Q.front()<<" ";
                    Q.pop();
                    cout<<Q.front()<<endl;
                    Q.pop();
        }
    }
}

int main(){
    cin >> n;
    items.resize(n);
    for(int i=0; i<n; i++){
        items[i].id=i;
        cin >> items[i].weight;
    }
    for(int i=0; i<n; i++){
        cin >> items[i].profit;
        items[i].profit_per_unit=items[i].profit/items[i].weight;
        //원래는 float형이 맞으나 문제 조건에 따라 int형 나눗셈 수행
    }

    //PQ를 통해 items를 정렬하기
    priority_queue<item, vector<item>, compare_item> pq;
    for(int i=0; i<n; i++){
        pq.push(items[i]);
    }

    for(int i=0; i<n;i++){
        items[i]=pq.top();
        pq.pop();
    }

    cin >> T;
    W.resize(T);
    for(int i=0; i<T; i++){
        cin >> W[i];
    }

    knapsack1();

    return 0;
}
