#include <iostream>
#include <vector>
using namespace std;

vector<int> vcolor;//가능한 color조합을 담는 배열
vector<vector<bool>> W;//각 vertex의 인접관계를 알려주는 배열
int n;//vertex 개수
int count_cases=0;//모든 색칠의 경우의 수
bool can_color=false;//색칠이 가능한 경우인지 아닌지 결정
int m;//색의 수 다만, 4색 정리로 인해 m=4부터는 무조건 색을 칠할 수 있음

bool promising(int i){
    int j=1;
    bool flag=true;

    while(j<i&&flag){
        if(W[i][j]&&vcolor[i]==vcolor[j])
            flag=false;
        j++;
    }
    return flag;
}

void m_coloring(int i){
    int color;

    if(promising(i)){
        if (i==n){
            can_color=true;
            count_cases++;
        }
        else
            for(color=1; color<=m; color++){
                vcolor[i+1]=color;
                m_coloring(i+1);
            }
    }
}

int main(){
    cin>>n;
    vcolor.resize(n+1);
    W.resize(n+1, vector<bool>(n+1));

    int k;
    cin>>k;
    int a,b;
    for(int i=0; i<k; i++){
        cin>>a>>b;
        W[a][b]=true;
        W[b][a]=true;
    }

    for(m=1; m<=4; m++){
        m_coloring(0);
        if(can_color) break;
    }

    cout<<m<<endl<<count_cases;

    return 0;
}