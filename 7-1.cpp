#include <iostream>
#include <vector>
using namespace std;

#define INF 0xffff
//define문에서는 세미콜론 붙이지 말자

typedef vector<vector<int>> matrix_t;
typedef pair<int, int> edge_t;
typedef vector<edge_t> set_of_edges;//edge_t뒤에 써줘야함


void prim(int n, matrix_t &W, set_of_edges& F){
    int vnear, min;
    vector<int> nearest(n+1), distance(n+1);
    F.clear();//vector 초기화
    for(int i=2; i<=n; i++){
        nearest[i]=1;
        distance[i]=W[1][i];
    }
    for(int k=0; k<n-1; k++){
        
        cout<< nearest[2];
        for(int i=3; i<=n; i++){
            cout << " " <<nearest[i];
        }
        cout<< endl;

        min=INF;
        for(int i=2; i<=n; i++)
            if(0<=distance[i] && distance[i]<min){
                min=distance[i];
                vnear=i;
            }
        F.push_back(make_pair(vnear, nearest[vnear]));
        distance[vnear]=-1;
        for(int i=2; i<=n; i++){
            if(distance[i] > W[i][vnear]){
                distance[i] = W[i][vnear];
                nearest[i]=vnear;
            }
        }
    }
     cout<< nearest[2];
    for(int i=3; i<=n; i++){
        cout << " " <<nearest[i];
    }
    cout<< endl;    
}

int main(){
    set_of_edges F;

    int n, m;
    cin >> n>>m;

    matrix_t W(n+1, vector<int>(n+1, INF));
    int u, v, w;
    for(int i=0; i<=n; i++){
        W[i][i]=0;
    }
    for(int i=0; i<m; i++){
        cin >> u>>v>>w;
        W[u][v]=w;
        W[v][u]=w;
    }

    prim(n, W, F);
    for(edge_t e: F){
        int u=e.first; 
        int v=e.second;
        cout << u << " "<< v << " "<<W[u][v]<<endl;
    }
    return 0;
}

