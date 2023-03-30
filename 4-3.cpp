#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> vector_t;
vector_t board;
int tromino_num=0;

void tromino(int init_row, int init_col, int n, int row, int col);
void fill(int mid_row, int mid_col, int quad);
void print_board(int n);


void tromino(int init_row, int init_col, int n, int row, int col){
    //트로미노는 중앙, 왼쪽위(1사분면), 오른쪽위(2사분면), 
    //왼쪽아래(3사분면), 오른쪽아래(4사분면) 순서로 채워져야 함
    int mid_row, mid_col;
    mid_row=init_row+n/2;
    mid_col=init_col+n/2;

    int quad_row[4]={mid_row-1, mid_row-1, mid_row, mid_row};
    int quad_col[4]={mid_col-1, mid_col, mid_col-1, mid_col};
    //각 사분면마다 (4번) 재귀할 것인데, 이 때 필요한 row, col 기본값 지정

    int quad=0;
    if(row<mid_row && col<mid_col)
        quad=1;
    if(row<mid_row && col>=mid_col)
        quad=2;
    if(row>=mid_row && col<mid_col)
        quad=3;
    if(row>=mid_row && col>=mid_col)
        quad=4;

    fill(mid_row, mid_col, quad);
    quad_row[quad-1]=row;
    quad_col[quad-1]=col;

    int m=n/2;
    if(m>1){
    tromino(init_row, init_col, m, quad_row[0], quad_col[0]);//1사분면
    tromino(init_row, mid_col, m, quad_row[1], quad_col[1]);//2사분면
    tromino(mid_row, init_col, m, quad_row[2], quad_col[2]);//3사분면
    tromino(mid_row, mid_col, m, quad_row[3], quad_col[3]);//4사분면
    }
}

void fill(int mid_row, int mid_col, int quad){
    tromino_num+=1;
    if(quad != 1)
        board[mid_row-1][mid_col-1]=tromino_num;
    if(quad != 2)
        board[mid_row-1][mid_col]=tromino_num;
    if(quad != 3)
        board[mid_row][mid_col-1]=tromino_num;
    if(quad != 4)
        board[mid_row][mid_col]=tromino_num;
}

void print_board(int n){
    for(int i=0; i<n; i++){
        cout<<board[i][0];
        for(int j=1; j<n; j++)
            cout<< " "<< board[i][j];
        cout<<endl;
        }
}


int main(){
    int n, row, col;
    cin >> n >> row>> col;
    //이때 n은 2의 거듭제곱수
    board.resize(n, vector<int>(n, 0));
    tromino(0,0, n, row, col);
    print_board(n);

    return 0;
}