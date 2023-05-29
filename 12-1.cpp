#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;//n: 아이템의 개수
int W;//W: 베낭의 무게

vector<int> p, w;
//p: 각 아이템에 대한 profit
//w: 각 아이템에 대한 weight

int maxprofit=0;

//아이템 정렬을 위한 item 구조체와 PQ의 compare 생성
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
        return true;//j가 우선순위가 높다
    return false;//i가 우선순위가 높다
    }
};

//compare생성과 Branch&Bound를 위한 노드 구조체 생성
typedef struct node* node_pointer;
typedef struct node{
    int level;
    int weight;
    int profit;
    float bound;
} nodetype;

//Best-Search-Tree탐색을 위한 PQ와 compare 생성
struct compare{
    bool operator()(node_pointer u, node_pointer v){
        if(u->bound < v->bound)
            return true;
        else
            return false;
    }
};

typedef priority_queue<node_pointer, vector<node_pointer>, compare>
        priority_queue_of_node;

//bound값을 구해주는 함수
float bound(node_pointer u){
    int j, k, totweight;
    float result;
    if(u->weight >= W)
        return 0;
    else{
        result=u->profit;
        j=u->level+1;
        totweight= u->weight;
        while(j<=n && totweight + w[j] <= W){
        //totweight가 W를 넘지 않을때까지 u의 다음 노드의 w를 totweight에 추가
            totweight += w[j];
            result += p[j];
            j++;
        }
        k=j;
        if(k<=n)
        //W를 가득채우도록 k의 w를 부분적으로 넣어줌
            result+=(W-totweight)*((float)p[k]/w[k]);
        return result;
    }
}

//bound를 자동으로 기입하고 malloc하기 위한 creat_node 함수
node_pointer create_node(int level, int weight, int profit){
    node_pointer v = (node_pointer)malloc(sizeof(nodetype));
    v->level=level;
    v->weight=weight;
    v->profit=profit;
    v->bound=bound(v);
    return v;
}

//Best Search Tree(+Priority Queue)를 이용한 Branch and Bound을 통해 knapsack 만들기
void knapsack6(){
    priority_queue_of_node PQ; node_pointer u,v;
    maxprofit=0;
    u=create_node(0,0,0);
    PQ.push(u);
    //출력 1. promising하든 하지 않든 방문한 노드 출력
    cout<<u->level<<" "<<u->weight<<" "<<u->profit<<" "<<u->bound<<endl;
    while(!PQ.empty()){
        //종료조건은 PQ가 empty일때
        v=PQ.top();
        PQ.pop();
        if(v->bound >maxprofit){//v가 유망할때 실행
            //1. u에 v의 다음 노드의 w, p를 포함시켰을 때
            u=create_node(v->level+1, v->weight+w[v->level+1], v->profit+p[v->level+1]);
            //출력 2. promising하든 하지 않든 방문한 노드 출력
            cout<<u->level<<" "<<u->weight<<" "<<u->profit<<" "<<u->bound<<endl;
            if(u->weight<=W&&u->profit>maxprofit)
                //maxprofit 갱신
                maxprofit=u->profit;
            if(u->bound > maxprofit)//promising하면 push
                PQ.push(u);
            //2. u에 v의 다음 노드의 p, w를 포함시키지 않았을 때
            u=create_node(v->level+1, v->weight, v->profit);
            //출력 3. promising하든 하지 않든 방문한 노드 출력
            cout<<u->level<<" "<<u->weight<<" "<<u->profit<<" "<<u->bound<<endl;
            if(u->bound > maxprofit)//promising하면 push
                PQ.push(u);
        }
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

    knapsack6();
    cout<<maxprofit<<endl;
}