#include <iostream>
#include <vector>
using namespace std;

#include <queue>
#include <map>

typedef struct node *node_ptr;
typedef struct node{
    char symbol;
    int frequency;
    node_ptr left;
    node_ptr right;
}node_t;

struct compare{
    bool operator()(node_ptr p, node_ptr q){
        return p->frequency > q->frequency;
    //부모노드인 p가 현재 노드인 q보다 크면 swap
    //즉, 이 compare을 사용하는 우선순위 큐는 min heap
    //(루트 노드가 가장 작은 가중치를 갖는 heap)
    }
};
//compare함수 뒤에는 세미콜론 붙이기

typedef priority_queue<node_ptr, vector<node_ptr>, compare> PriorityQueue;
//우선순위큐를 만들기 위해 <queue> 필요

node_ptr create_node(char name, int frequency1, int frequency2){
    node_ptr p=new node_t;
    p->symbol=name;
    p->frequency=frequency1+frequency2;
    p->left=NULL;
    p->right=NULL;
    return p;
}

void huffman(int n, PriorityQueue& PQ){//PQ를 인코딩과 디코딩을 위해 재구성
    for(int i=1; i<=n-1; i++){
        node_ptr p= PQ.top(); PQ.pop();
        node_ptr q=PQ.top(); PQ.pop();
        node_ptr r=create_node('+', p->frequency, q->frequency);
        r->left=p;
        r->right=q;
        PQ.push(r);
    }
}

void make_encoder(node_ptr node, string code, map<char, string> &encoder){
    //map을 사용하려면 <map> 필요
    //encoder표를 만드는 함수(한번만 사용)
    if(node->symbol != '+'){
        encoder[node->symbol]=code;
    }
    else{
        make_encoder(node->left, code+"0", encoder);
        make_encoder(node->right, code+"1", encoder);
    }
}

void decode(node_ptr root, node_ptr node, string s, int i){
    //root는 root 노트, node는 현재 노드, s는 디코딩할 문자, i는 s의 인덱스
    if(i<=s.length()){
        if(node->symbol != '+'){//값을 찾았다면
            cout << node->symbol;
            decode(root, root, s, i);//원점(root)로 회귀
        }
        else{//+라면 
            if(s[i]=='0')
                decode(root, node->left, s, i+1);
            else
                decode(root, node->right, s, i+1);
        }
    }
}

void inorder(node_ptr ptr){
    if(ptr){
        inorder(ptr->left);
        cout<< ptr->symbol<<":"<<ptr->frequency<<" ";
        inorder(ptr->right);
    }
}

void preorder(node_ptr ptr){
    if(ptr){
        cout<< ptr->symbol<<":"<<ptr->frequency<<" ";
        preorder(ptr->left);
        preorder(ptr->right);

    }
}

int main(){
    //PQ input
    int n;
    cin>>n;
    vector<node_ptr> ptr_list(n);
    map<char, string> encoder;
    char c;
    for(int i=0; i<n; i++){
        ptr_list[i]= new node_t;
        cin >> c;
        ptr_list[i]->symbol=c;
        encoder.insert(make_pair(c, "0"));
        //encoder에 값 넣기
        ptr_list[i]->left=NULL;
        ptr_list[i]->right=NULL;
    }
    for(int i=0; i<n; i++){
        cin >> ptr_list[i]->frequency;
    }

    PriorityQueue PQ;
    for(int i=0; i<n; i++){
        PQ.push(ptr_list[i]);
    }
    huffman(n, PQ);
    node_ptr root=PQ.top();

    //encode input

    make_encoder(root, "", encoder);

    int encode_n;
    cin >> encode_n;

    vector<string> encode_list(encode_n);
    for(int i=0; i<encode_n; i++){
        cin >> encode_list[i];
    }

    //decode input
    int decode_n;
    cin >> decode_n;

    vector<string> decode_list(decode_n);
    for(int i=0; i<decode_n; i++){
        cin >> decode_list[i];
    }

    //PQ output
    preorder(root);
    cout<<endl;
    inorder(root);
    cout<<endl;
    
    //encode output
    for(int i=0; i<encode_n; i++){
        for(char c: encode_list[i]){
            cout<< encoder[c];
        }
        cout<<endl;
    }

    //decode output
    for(int i=0; i<decode_n; i++){
        decode(root, root, decode_list[i], 0);
        cout<<endl;
    }

    return 0;
}
