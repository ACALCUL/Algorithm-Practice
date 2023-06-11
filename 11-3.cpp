#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph;
int cnt;

void make_graph(int n, int m){
    int imove[8]={-2, -1, 1, 2, 2, 1, -1, -2};
    int jmove[8]={1, 2, 2, 1, -1, -2, -2, -1};
    graph.resize(m*n);
    int ni, nj;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            for(int k=0; k<8; k++){
                ni=i+imove[k];
                nj=j+jmove[k];
                //(i, j)에 있는 Knight가 이동 가능한 좌표: (ni, nj)
                if((ni>=0)&&(ni<n)&&(nj>=0)&&(nj<m))
                    graph[i*m+j].push_back(ni*m+nj);
                //graph[i*m+j]에는 (i, j)좌표에서 Knight가 이동 가능한 좌표를 ni*m+nj형식으로 push
            }
}

void tour_circuit(int k, int v, int s, int n, int m, vector<int> mark){
    //k: 방문횟수, v: 현재 point, s: 출발 point,
    //k, v, s는 원래 2차원이여야 하나 i*m+j형태로 1차원으로 압축함
    //n: 행의 개수, m: 열의 개수, mark: vertex를 1차원으로 압축한 것에 대한 방문 순서를 저장

    if(k==n*m){
        bool opt=false;
        for(int i: graph[v])
            if(i==s){
            //graph[v] 배열에 시작지점 s와 같은 vertex가 있으면 true
                opt=true;
                break;
            }
        if(opt){
            mark[v]=k;
            
            /* for(int i=1; i<=k; i++){
                for(int j=0; j<mark.size(); j++){
                    if(mark[j]==i){
                        cout<<"("<<j/m<<", "<<j%m<<") ";
                        //cout<<j<<" ";
                        //위는 2차원 형태 아래는 1차원 압축 형태
                        break;
                    }
                }
            }
            cout<<endl; */
            
            cnt++;
            //cnt는 해밀턴 회로의 개수
        }
    }
    else
        for(int u: graph[v])//v에서 Knight가 이동 가능한 모든 점 u에 대해서
            if(mark[u]==0){//u를 방문한 적 없다면
                mark[u]=k+1;//u를 다음으로 방문했다고 하고
                tour_circuit(k+1, u, s, n, m, mark);//그렇게 했을 때를 재귀 호출
                mark[u]=0;
            }
}

void tour_path(int k, int v, int s, int n, int m, vector<int> mark){
    //k: 방문횟수, v: 현재 노드, s: 출발노드,
    //n: 행의 개수, m: 열의 개수, mark: 방문 순서를 저장하는 배열

    if(k==n*m){
        //해밀텅 회로에서 시작 지점과 같은 vertex가 있어야 한다는 조건만 빠짐
        mark[v]=k;
        cnt++;
    }
    else
        for(int u: graph[v])
            if(mark[u]==0){
                mark[u]=k+1;
                tour_path(k+1, u, s, n, m, mark);
                mark[u]=0;
            }
}

int main(){
    int n, m;
    //n: 행의 개수, m: 열의 개수
    int T;
    //T: 출발 정점의 개수
    cin>>n>>m>>T;

    vector<int> row(T);
    vector<int> col(T);
    for(int i=0; i<T; i++){
        cin>>row[i]>>col[i];
    }

    vector<int> mark(n*m, 0);
    make_graph(n, m);
    cnt=0;
    int s=0;
    mark[s]=1;
    tour_circuit(1, s, s, n, m, mark);
    cout<<cnt<<endl;

    for(int i=0; i<T; i++){
        fill(mark.begin(), mark.end(), 0);
        cnt=0;
        s=row[i]*m+col[i];
        mark[s]=1;
        tour_path(1, s, s,n,m, mark);
        cout<<cnt<<endl;
    }
}