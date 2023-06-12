#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

const int INF = 0x7fffffff;
//int는 4byte=32bits
//7은 0111 따라서 INF는 int형의 최댓값
typedef vector<vector<int>> matrix_t;

//count는 A집합 안에 있는 vertex의 개수를 리턴
int count(int A){
    int cnt=0;
    for(; A!=0; A>>=1)
        if(A&1)
            cnt++;
    return cnt;
}

//isIn은 A집합 안에 i번째 vertex가 있는지 반환
bool isIn(int i, int A){
    return (A & (1 << (i-2))) != 0;
}

//diff는 A에서 j번째 vertex를 제외한 집합을 리턴
int diff(int A, int j){
    return (A & ~(1 << (j-2)));
}

//minimum은 i, W, D를 통해 
//i번째 vertex에서 시작하여 A집합안에 포함된 vertex를 경우하는 최솟값 리턴
//그리고 최솟값일때의 j를 저장
int minimum(int n, int i, int &minJ, int A, matrix_t& W, matrix_t& D){
    int minV=INF, value;
    for(int j=2; j<=n; j++){
        if(!isIn(j,A)) continue;
        int value=W[i][j]+D[j][diff(A,j)];
        if(minV>value){
            minV=value;
            minJ=j;
        }
    }
    return minV;
}

//travel은 n, W를 통해 D, P, minlength를 채워줌
void travel(int n, matrix_t& W, matrix_t& D, matrix_t& P, int &minlength){
    //D와 P의 행은 n+1개, 열은 A의 최대값+1인 pow(2, n-1)개
    //D와 P의 첫번째 인자는 시작 vertex i, 두번째 인자는 경유할 vertex의 집합인 A
    //D는 min값 저장, P는 min일때의 시작 vertex i의 다음 경유지인 j값 저장
    int i, j, k, A;

    int subset_size=pow(2, n-1);//A의 최댓값
    for(i=2; i<=n; i++)
        //A=0(공집합)일때는 D가 시작점 i와 끝점 1의 거리
        D[i][0]=W[i][1];
    for(k=1; k<=n-2; k++)
    //k는 A집합의 vertex 개수
    //개수가 1일때부터 해야 D가 정상적으로 기입됨
    //(v1, vi 제외하므로 k의 최대값 n-2)
        for(A=0; A<subset_size; A++){
            if(count(A) != k) continue;
            //count(A)는 A집합에 포함된 vertex 개수 리턴
            //vertex 개수가 k일때만 뒤의 코드 실행
            for(i=2; i<=n; i++){
                if(isIn(i, A)) continue;
                //i가 A집합에 포함되어 있다면 뛰어넘기
                D[i][A]=minimum(n, i, j, A, W, D);
                P[i][A]=j;
            }
        }
    
    A=subset_size-1;
    //A를 v1을 제외한 모든 vertex집합으로 설정
    D[1][A]=minimum(n, 1, j, A, W, D);
    P[1][A]=j;
    minlength=D[1][A];
}

//tour은 optimal 경로를 출력
void tour(int v, int A, matrix_t& P){
    int k= P[v][A];
    if(A==0)
        cout<<"1";
    //마지막에 A가 공집합이 되었을 때 1번째 v가 도착지점이므로
    else{
        cout<<k<<" ";
        tour(k, diff(A, k), P);
    }
}

int main(){
    int n, m;
    //n은 vertex 개수, m은 edge 개수
    cin>>n>>m;
    matrix_t W(n+1, vector<int>(n+1, INF));
    for(int i=1; i<=n; i++){
        W[i][i]=0;
    }
    int v1, v2, value;
    for(int i=0; i<m; i++){
        cin>>v1>>v2>>value;
        W[v1][v2]=value;
    }
    
    int subset_size=pow(2, n-1);
    matrix_t D(n+1, vector<int>(subset_size, INF));
    matrix_t P(n+1, vector<int>(subset_size, 0));
    
    int minlength;
    travel(n, W, D, P, minlength);
    cout<<minlength<<endl;
    
    cout<<1<<" ";
    tour(1, subset_size-1, P);
    cout<<endl;

    for(int i=0; i<n+1; i++){
        for(int j=0; j<subset_size; j++){
            value=D[i][j];
            if(D[i][j]==INF) continue;
            cout<<i<<" "<<j<<" "<<D[i][j]<<endl;
        }
    }
}