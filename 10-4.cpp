#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> W;//인접한 vertex인지를 알려주는 배열
vector<int> vindex;//해밀턴 회로가 충족이 되는 vertex 배열을 담는 공간
//vindex는 0~n-1이고, 노드 이름은 1~n이다.
int n;//vertex 개수
int count_cases=0;//해밀턴 경로가 충족되는 경우의 수의 개수

bool promising(int i){
    int j;
    bool flag;
    if(i==n-1&&!W[vindex[n-1]][vindex[0]])
        flag=false;
    else if(i>0 && !W[vindex[i-1]][vindex[i]])
        flag=false;
    else{
        flag=true;
        j=1;
        while(j<i && flag){
            if(vindex[i]==vindex[j])
                flag=false;
            j++;
        }
    }
    return flag;
}

void hamiltonian(int i){
    int j;
    if(promising(i)){
        if(i==n-1){
            //cout<<"add!"<<endl;
            count_cases++;
        }
        else
            for(j=2; j<=n; j++){
                vindex[i+1]=j;
                hamiltonian(i+1);
            }
    }
}

int main(){
    cin>>n;
    vindex.resize(n);
    //vindex는 0~n-1이고(또한 n과 0은 겹침), 노드 이름은 1~n이다.
    W.resize(n+1, vector<bool>(n+1));

    int m;
    cin>>m;
    int a,b;
    for(int i=0; i<m; i++){
        cin>>a>>b;
        W[a][b]=true;
        W[b][a]=true;
    }
    vindex[0]=1;
    hamiltonian(0);
    cout<<count_cases;

    return 0;
}