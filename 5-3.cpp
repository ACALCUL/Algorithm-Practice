#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;
#define INF 999;

void print_matrix(int n, matrix_t A){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(j==n){
                cout << A[i][j] <<endl;
            }
            else{
                cout << A[i][j]<< " ";
            }
        }
    }
    //cout << endl<< endl;
}


void floyd2(int n, matrix_t& W, matrix_t& D, matrix_t& P){
    for(int i=1; i<=n;i++){
        for(int j=1; j<=n;j++){
            D[i][j]=W[i][j];
            P[i][j]=0;
        }
    }
    for(int k=1; k<=n; k++){
        //cout<< "k: "<< k <<endl;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++){
                if(j==i){
                    D[i][j]=0;
                    continue;
                }    
                if(D[i][j]>D[i][k]+D[k][j]){
                    D[i][j]=D[i][k]+D[k][j];
                    P[i][j]=k;
                }
            }
        //print_matrix(n, D);
    }
}

void path(matrix_t& P, int u, int v){
    int k= P[u][v];
    //원래는 999대신 INF를 써야하지만 define 상수는 조건안에 못씀...
    //(쓰고 싶으면 #if문을 쓰거나 defin대신 const int를 하자)
    if(k !=0){
        path(P, u, k);
        cout << k <<" ";
        path(P, k, v);
    }
}


int main(){
    int N, M;
    //정점의 개수: N, 간선의 개수: M
    cin >> N >>M;

    matrix_t W(N+1, vector<int>(N+1, 0));
    //W는 각 점의 직결된 경로 거리
    //직결되지 않거나 같은 점끼리는 INFINITY
    matrix_t D(N+1, vector<int>(N+1));
    //D는 각 점에서 다른 점(2개 이상 가능)을 통과했을 때의 최단 경로 거리
    //같은 점끼리는 0
    matrix_t P(N+1, vector<int>(N+1));
    //P는 D를 생성할때 거쳐간 점의 종류
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            W[i][j]=INF;
        }
    }

    int u, v, w;
    for(int i=0; i<M; i++){
        cin >> u>> v>> w;
        W[u][v]=w;
    }

    int T;
    cin >> T;
    matrix_t pair(T, vector<int>(2));
    for(int i=0; i<T; i++){
        cin >> u >> v;
        pair[i][0]=u;
        pair[i][1]=v;
    }
 
    floyd2(N, W, D, P);
    print_matrix(N, D);
    print_matrix(N, P);

    for(int i=0; i<T; i++){
        u=pair[i][0];
        v=pair[i][1];
        if(D[u][v]==999){
            //조건문 안에 define 상수 못 넣어서 999라고 함
            //해결법 1. const int로 INF를 정의
            //해결법 2. #if문 사용
            cout<< "NONE"<< endl;
            continue;
        }
        cout<< u << " ";
        path(P, u, v);
        cout<< v <<endl;
    }

    return 0;
}