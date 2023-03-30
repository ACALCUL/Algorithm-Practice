#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;
int threshold;
int cnt=0;

void print_matrix(int n, matrix_t matrix){
    for(int i=0; i<n; i++){
        cout<< matrix[i][0];
        for(int j=1; j<n; j++){
            cout << " "<<matrix[i][j];
        }
        cout << endl;
    } 
}
matrix_t resize(int n, int k, matrix_t& matrix){
    vector<vector<int>> A(k, vector<int>(k, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            A[i][j]=matrix[i][j];
        }
    }
    return A;
}
matrix_t madd(int n, matrix_t A, matrix_t B){
    matrix_t C(n, vector<int>(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j]=A[i][j]+B[i][j];
    return C;
}
matrix_t msub(int n, matrix_t A, matrix_t B){
    matrix_t C(n, vector<int>(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j]=A[i][j]-B[i][j];
    return C;
}
matrix_t mmult(int n, matrix_t A, matrix_t B){
    matrix_t C(n, vector<int>(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            C[i][j]=0;
            for(int k=0; k<n; k++)
                C[i][j]+=A[i][k]*B[k][j];
            }
    return C;
}
void partition(int m, matrix_t M, matrix_t& M11, matrix_t& M12, matrix_t& M21, matrix_t& M22){
    for(int i=0; i<m; i++)
        for(int j=0; j<m; j++){
            M11[i][j]=M[i][j];
            M12[i][j]=M[i][j+m];
            M21[i][j]=M[i+m][j];
            M22[i][j]=M[i+m][j+m];
        }    
}
void combine(int m, matrix_t& M, matrix_t M11, matrix_t M12, matrix_t M21, matrix_t M22){
        for(int i=0; i<m; i++)
            for(int j=0; j<m; j++){
            M[i][j]=M11[i][j];
            M[i][j+m]=M12[i][j];
            M[i+m][j]=M21[i][j];
            M[i+m][j+m]=M22[i][j];
            }   
}
void strassen(int n, matrix_t A, matrix_t B, matrix_t& C){
    cnt++;

    if (n<=threshold){
            C = mmult(n, A, B);
    }
    
    else{
        int m=n/2;
        matrix_t A11(m, vector<int>(m));
        matrix_t A12(m, vector<int>(m));
        matrix_t A21(m, vector<int>(m));
        matrix_t A22(m, vector<int>(m));
        matrix_t B11(m, vector<int>(m));
        matrix_t B12(m, vector<int>(m));
        matrix_t B21(m, vector<int>(m));
        matrix_t B22(m, vector<int>(m));

        partition(m, A, A11, A12, A21, A22);
        partition(m, B, B11, B12, B21, B22);

        matrix_t M1(m, vector<int>(m));
        matrix_t M2(m, vector<int>(m));
        matrix_t M3(m, vector<int>(m));
        matrix_t M4(m, vector<int>(m));
        matrix_t M5(m, vector<int>(m));
        matrix_t M6(m, vector<int>(m));
        matrix_t M7(m, vector<int>(m));

        strassen(m, madd(m, A11, A22), madd(m, B11, B22), M1);
        strassen(m, madd(m, A21, A22), B11, M2);
        strassen(m, A11, msub(m, B12, B22),M3);
        strassen(m, A22, msub(m, B21, B11),M4);
        strassen(m, madd(m, A11, A12), B22, M5);
        strassen(m, msub(m, A21, A11), madd(m, B11, B12),M6);
        strassen(m,  msub(m, A12, A22), madd(m, B21, B22), M7);

        matrix_t C11(m, vector<int>(m));
        matrix_t C12(m, vector<int>(m));
        matrix_t C21(m, vector<int>(m));
        matrix_t C22(m, vector<int>(m));

        C11=madd(m, madd(m, M1, M4), msub(m, M7, M5));
        C12=madd(m, M3, M5);
        C21=madd(m, M2, M4);
        C22=madd(m, madd(m, M1, M3), msub(m, M6, M2));

        combine(m, C, C11, C12, C21, C22);
        
    }

}

int main(){
    int n, new_n; //print할 때는 n을 사용, strassen사용할 때는 new_n(k값) 사용
    cin >> n >> threshold;
    //cout << n << " "<<threshold;
    matrix_t A(n, vector<int>(n));
    matrix_t B(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> A[i][j];
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> B[i][j];
        }
    }

    new_n=1;
    while (new_n< n) 
        new_n*=2;

    A=resize(n, new_n, A);
    B=resize(n, new_n, B);

    matrix_t C(new_n, vector<int>(new_n));
    strassen(new_n, A, B, C);
    
    cout << cnt<< endl;
    print_matrix(n, C);
}