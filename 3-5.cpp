#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;

matrix_t mat_mul(int n, matrix_t A, matrix_t B);
matrix_t modul_expon(int n, int b, matrix_t V);


matrix_t mat_mul(int n, matrix_t A, matrix_t B){//기존 행렬의 곱셈에다가 모듈러도 포함됨
    matrix_t C(n, vector<int>(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            C[i][j]=0;
            for(int k=0; k<n; k++)
                C[i][j]+=((A[i][k]%1000)*(B[k][j]%1000))%1000;
            C[i][j]%=1000;
                //ab%N=((a%N)*(b%N))%N (문제에서 N=100)
            }
    return C;
}

matrix_t modul_expon(int n, int b, matrix_t V){
    if(b==1){
        return V;
    }
    else if(b==2){
        return mat_mul(n, V, V);
    }
    else if(b%2){//b가 홀수
    //V*(V의 b/2 거듭제곱)*(V의 b/2 거듭제곱)
        return mat_mul(n, V, modul_expon(n, b-1, V));
    }
    else{//b가 짝수
    //(V의 b/2 거듭제곱)*(V의 b/2 거듭제곱)
        matrix_t X;
        X=modul_expon(n, b/2, V);
        return mat_mul(n, X, X);
    }

}

int main(){
    int n, b;
    cin >> n >> b;
    matrix_t V(n, vector<int>(n));//V는 단위행렬
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> V[i][j];
/*     for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << V[i][j]<< " ";
        cout << endl;
        } */
    matrix_t W(n, vector<int>(n));
    //W는 V를 거듭제곱한 행렬(구하고자 하는 행렬)
    W=modul_expon(n, b, V);
    //cout<<"W matrix start!"<<endl;
    for(int i=0; i<n; i++){
        cout<<W[i][0];
        for(int j=1; j<n; j++)
            cout << " "<< W[i][j];
        cout << endl;
        } 
}
