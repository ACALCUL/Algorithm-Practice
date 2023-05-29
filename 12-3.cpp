#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 0x7ffffff;
//int는 4byte=32bits
//7은 0111 따라서 INF는 int형의 최댓값

int n;//vertex 개수
typedef vector<vector<int>> matrix_t;
matrix_t W;//undirected 가중치를 담는 이차원 배열

//node typedef하기
typedef vector<int> ordered_set;

typedef struct node *node_pointer;
typedef struct node {
    int level;
    ordered_set path;
    int bound;
}nodetype;

//branch and bound를 위해 bound를 우선순위로 하는 PQ 생성
struct compare{
    bool operator()(node_pointer u, node_pointer v){
        if(u->bound > v->bound)
            return true;
        else
            return false;
    }
};

typedef priority_queue<node_pointer, vector<node_pointer>, compare>
        priority_queue_of_node;

//length: W를 이용해 path의 길이 리턴
int length(ordered_set path){
    vector<int>::iterator it;
    int len=0;
    for(it=path.begin(); it != path.end(); it++){
        if(it != path.end()-1)
        //끝부분은 W를 추가 X
            len += W[*it][*(it+1)];
    }
    return len;
}

//hasOutgoing: path의 마지막 vertex를 제외하고 path에 v가 있으면 true
bool hasOutgoing(int v, ordered_set path){
    vector<int>::iterator it;
    for(it=path.begin(); it!=path.end()-1; it++)
        if(*it==v) 
            return true;
    return false;
}

//hasIncoming: path의 첫번째 vertex를 제외하고 path에 v가 있으면 true
bool hasIncoming(int v, ordered_set path){
    vector<int>::iterator it;
    for(it=path.begin()+1; it!=path.end(); it++)
        if(*it==v)
            return true;
    return false;
}

//bound: v의 loverbound(미래에 path에 vertex가 추가로 붙을 때의 length 최솟값) 리턴
int bound(node_pointer v){
    int lower=length(v->path);//기존에 가지고 있던 path의 length가 기본
    for(int i=1; i<=n ; i++){//추가할 W의 첫번째 인자
        if(hasOutgoing(i, v->path)) continue;
        int min=INF;
        for(int j=1; j<=n; j++){//추가할 W의 두번째 인자
            //Don't include self-loop
            if(i==j) continue;
            if(j==1 && i==v->path[v->path.size()-1]) continue;
            //첫번째 vertex말고 path에 있으면 뛰어넘기
            if(hasIncoming(j, v->path)) continue;
            //min값 갱신
            if(min > W[i][j]) min=W[i][j];
        }
        lower+=min;
    }
    return lower;
}


node_pointer create_node(int level, ordered_set path){
    node_pointer v = new node;
    //new를 써서 동적할당을 해주면 멤버가 가변적이여도 메모리가 맞춰서 바뀜
    v->level=level;
    v->path.resize(path.size());
    copy(path.begin(), path.end(), v->path.begin());
    v->bound=bound(v);
    return v;
}

bool isIn(int v, ordered_set path){
    for(int i: path){
        if(i==v)
            return true;
    }
    return false;
}

int remaining_vertex(ordered_set path){
    for(int i=2; i<=n; i++){
        if(!isIn(i, path)){
            return i;
        }
    }
    cout<<"isIn이 비정상적으로 작동함"<<endl;
    return 0;
}

void print_node(node_pointer u){
    cout<<u->level<<" ";
    if(u->bound<0x0000ffff)
            cout<<u->bound;
        else
            cout<<"INF";
    for(int i: u->path){
        cout<<" "<<i;
    }
    cout<<endl;
}

//travel2: W를 통해 opttour와 minelength를 채우는 함수
void travel2(ordered_set &opttour, int& minlength){
    priority_queue_of_node PQ;
    node_pointer u, v;

    minlength=INF;
    ordered_set init_path;
    init_path.push_back(1);
    v= create_node(0, init_path);
    //level 0으로 시작, 1은 기본적으로 path에 들어감
    PQ.push(v);

    print_node(v);//출력 1


    while(!PQ.empty()){//PQ.empty가 종료 조건
        v=PQ.top();
        PQ.pop();
        
        if(v->bound < minlength){ //v가 유망하면 조건문 실행
            for(int i=2; i<=n; i++){//i는 path에 추가할 vertex
                if(isIn(i, v->path)) continue;//path에 i가 있으면 뛰어넘기
                u=create_node(v->level+1, v->path);
                u->path.push_back(i);
                if(u->level == n-2){//path에 들어갈 모든 vertex가 확정되었으면
                    u->bound=bound(u);
                    u->path.push_back(remaining_vertex(u->path));
                    u->path.push_back(1);
                    print_node(u);//출력2
                    if(length(u->path) < minlength){//minlength 결정
                        minlength = length(u->path);
                        copy(u->path.begin(), u->path.end(), opttour.begin());
                    }
                }
                else{
                    u->bound=bound(u);
                    print_node(u);//출력3
                    if(u->bound < minlength){//u가 유망하면
                        PQ.push(u);
                    }
                }
            }
        }

    }
}

int main(){
    int m;
    //m은 edge 개수
    cin>>n>>m;
    W.resize(n+1, vector<int>(n+1, INF));
    for(int i=1; i<=n; i++){
        W[i][i]=0;
    }
    int v1, v2, value;
    for(int i=0; i<m; i++){
        cin>>v1>>v2>>value;
        W[v1][v2]=value;
    }
    
    int minlength;
    ordered_set opttour(n+1);//최적의 tour를 담는 vector
    travel2(opttour, minlength);
    cout<<minlength<<endl;

    cout<<opttour[0];
    for(int i=1; i<opttour.size(); i++){
        cout<<" "<<opttour[i];
    }
}