//기본적으로 7-1 prim's algorithm을 베낌
#include <iostream>
#include <vector>
using namespace std;

#define INF 0xffff
//define문에서는 세미콜론 붙이지 말자

typedef vector<vector<int>> matrix_t;
typedef pair<int, int> edge_t;
typedef vector<edge_t> set_of_edges;//edge_t뒤에 써줘야함


void dijkstra(int n, matrix_t &W, set_of_edges& F, vector<int> &touch, vector<int>& length){
    //인자에 touch와 length 추가(length는 문제 조건에 필요없긴 하지만..)
    int vnear, min;
    
    F.clear();//vector 초기화
    
    touch[1]=0; length[1]=0;
    for(int i=2; i<=n; i++){
        touch[i]=1;
        length[i]=W[1][i];
    }
    for(int k=0; k<n-1; k++){
        
        cout<< touch[2];
        for(int i=3; i<=n; i++){
            cout << " " <<touch[i];
        }
        cout<< endl;

        min=INF;
        for(int i=2; i<=n; i++)
            if(0<=length[i] && length[i]<min){
                min=length[i];
                vnear=i;
            }
        F.push_back(make_pair(vnear, touch[vnear]));
        for(int i=2; i<=n; i++){//
            if(length[i] > length[vnear]+W[vnear][i]){
                //prim과 다른 건 length만 넣는 대신 length+W를 한다는 점
                length[i] = length[vnear]+W[vnear][i];
                touch[i]=vnear;
            }
        }
        length[vnear]=-1;
    }
    cout<< touch[2];
    for(int i=3; i<=n; i++){
        cout << " " <<touch[i];
    }
    cout<< endl;
}

void print_path(int dest, vector<int> touch){
    int n=dest;
    vector<int> path;
    while(n != 1){
        path.push_back(n);
        n = touch[n];
    }
    path.push_back(1);

    //cout<<"print dest="<<dest<<endl;
    cout<< path[path.size()-1];
    for(int i=path.size()-2 ; i>=0; i--){
        cout << " "<<path[i];
    }
    cout << endl;
}

void print_matrix(int m, int n, matrix_t& A){
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            cout << A[i][j]<<" ";
        }
        cout<<endl;
    }
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
    }

    int t;
    cin>> t;
    vector<int> T(t);
    for(int i=0; i<t; i++ ){
        cin >> T[i];
    }

    //print_matrix(n, n, W);

    vector<int> touch(n+1, 0), length(n+1, 0);

    dijkstra(n, W, F, touch, length);
    for(edge_t e: F){
        int u=e.first; 
        int v=e.second;
        cout <<v << " "<< u << " "<<W[v][u]<<endl;
    }

    for(int i=0; i<t; i++ ){
        int dest=T[i];
        print_path(dest, touch);
    }
    
    return 0;
}