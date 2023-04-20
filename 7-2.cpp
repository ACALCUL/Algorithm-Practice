#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct edge{
    int u, v, w;
}edge_t;

struct edge_compare{
    bool operator()(edge_t e1, edge_t e2){
        //operator: 연산자 오버로딩
        if(e1.w>e2.w) return true;
        else return false;
    }
};

typedef vector<edge_t> set_of_edges;
typedef priority_queue<edge_t, vector<edge_t>, edge_compare> PriortyQueue;
//priority_queue를 쓰기위해서는 <queue>필요
//priority queue는 edge_t형으로 vector<edge_t>에 저장, 그리고 edge_compare를 통해 가중치 결정

vector<int> dset;

void dset_init(int n){
    dset.resize(n+1);
    for(int i=1; i<=n; i++){
        dset[i]=i;
    }
}

int dset_find(int i){
    while(dset[i] != i){
        i=dset[i];
    }
    return i;
}

void dset_merge(int p, int q){
    dset[p]=q;
}

//여기에다가 dest_collapse를 넣는데 시간복잡도 향상에 도움이 된다.

void kruskal(int n, int m, set_of_edges& E, set_of_edges& F){
    int p, q;
    edge_t e;
    PriortyQueue PQ;

    for (edge_t e: E){
        PQ.push(e);
        //priorty queue는 push를 사용
    }

    F.clear();
    dset_init(n);

    while(F.size()<n-1){
        e=PQ.top();
        PQ.pop();
        //top을 pop
        p=dset_find(e.u);
        q=dset_find(e.v);
        //cout<<e.u<<"->"<<p<<", "<<e.v<<"->"<<q<<endl;
        if(p!=q){//u와 v의 find값이 같지 않다면(edge를 추가했을 때 cycle이 형성되지 않는다면)
            dset_merge(p, q);
            F.push_back(e);
        }
    }

}

int main(void){

    int n, m;
    cin >> n>>m;
    set_of_edges E(m);

    int u, v, w;
    for(int i=0; i<m; i++){
        cin >> u>>v>>w;
        E[i].u=u;
        E[i].v=v;
        E[i].w=w;
    }

    set_of_edges F(n-1);

    kruskal(n, m, E, F);
    for(edge_t e: F){
        u=e.u; 
        v=e.v;
        w=e.w;
        cout << u << " "<< v << " "<<w<<endl;
    }
    return 0;
}