#include <iostream>
#include <vector>
using namespace std;

typedef struct node* node_ptr;
typedef struct node{
    int key;
    node_ptr left;
    node_ptr right;
}node_t;

typedef vector<vector<int>> matrix_t;
const int INF = 0x7fffffff;
int node_cnt =0;
//node_cnt는 뒷공백을 없애기 위한 상수

int minimum(int i, int j, int& mink, vector<int> &p, matrix_t& A){
    int minvalue = INF, value;
    for(int k= i; k<= j; k++){
        value=A[i][k-1]+A[k+1][j];
        if(minvalue > value){
            minvalue = value;
            mink = k;
        }
    }
    for(int k=i; k<=j; k++){
        minvalue+=p[k];
    }
    return minvalue;
}

void opsearchtree(int n, vector<int>& p, matrix_t& A, matrix_t& R){
    for(int i=1; i<=n; i++){
        A[i][i-1]=0;
        A[i][i]=p[i];
        R[i][i-1]=0;
        R[i][i]=i;
    }
    A[n+1][n]=R[n+1][n]=0;

    for(int diag =1 ; diag <= n-1; diag++){
        for(int i=1; i<=n-diag; i++){
            int k, j=i+diag;
            A[i][j]=minimum(i, j, k, p, A);
            R[i][j]=k;
        }
    }
}

node_ptr create_node(int i){
    //중요!
    node_ptr node=new struct node;
    //노드에 메모리 할당을 해줘야 한다!
    node->key=i;
    node->left=NULL;
    node->right=NULL;
    //node 생성시 left, right child를 NULL로 무조건 해줘야함(재귀 끝부분에서 사용됨)
    return node;
}

node_ptr tree(int i, int j, vector<int>& keys, matrix_t& R){
    int k=R[i][j];
    if(k==0)
        return NULL;
    else{
        node_ptr node = create_node(keys[k]);
        node->left=tree(i, k-1, keys, R);
        node->right=tree(k+1, j, keys, R);
        return node;
    }
}

void inorder(node_ptr ptr){
    if(ptr){
        inorder(ptr->left);
        if(node_cnt++){
            cout<< " "<< ptr->key;
        }
        else
            cout<<ptr->key;
        inorder(ptr->right);
    }
}

void preorder(node_ptr ptr){
    if(ptr){
        if(node_cnt++){
            cout<< " "<< ptr->key;
        }
        else
            cout<<ptr->key;
        preorder(ptr->left);
        preorder(ptr->right);

    }
}

void print_uptri(int n, matrix_t A){
    for(int i=1; i<=n+1; i++){
        cout<< A[i][i-1];
        //6-1과는 다르게 i는 n+1까지 j는 i-1부터해야 앞에 0들을 출력 가능
        for(int j=i; j<=n; j++){
            cout<< " "<<A[i][j]; 
        }
        cout<< endl;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> keys(n+1);
    for(int i=1; i<=n; i++){
        cin >> keys[i];
    }
    vector<int> p(n+1);
    //p가 양의 정수값이 아닌 실수값으로 주어지면 vector<float>써야함
    for(int i=1; i<=n; i++){
        cin >> p[i];
    }

    matrix_t A(n+2, vector<int>(n+2));
    matrix_t R(n+2, vector<int>(n+2));
    //둘다 인덱스가 n+1원소(n+1원소들은 모두 값이 0)까지 사용하므로 n+2로 초기화
    //vector 자료형은 기본적으로 모든 값이 0으로 초기화

    opsearchtree(n, p, A, R);

    print_uptri(n, A);
    print_uptri(n, R);

    cout << A[1][n]<< endl;
    node_ptr result_node = tree(1, n, keys, R);
    node_cnt=0;
    preorder(result_node);
    cout<<endl;
    node_cnt=0;
    //뒷공백 없애주기 위해 node_cnt를 0으로 다시 초기화
    inorder(result_node);
    

    return 0;
}