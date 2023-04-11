#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> matrix_t;
const int INF = 0x7fffffff;
//7은 0111이므로 맨앞에 7이고, 7fffffff는 32비트인 int의 최댓값이다
//INT_MAX를 써도 되지만 <climits>필요


int minimum(int i, int j, int& mink, vector<int> &d, matrix_t& M){
    int minvalue = INF, value;
    for(int k= i; k<= j-1; k++){
        value=M[i][k]+M[k+1][j]+d[i-1]*d[k]*d[j];
        if(minvalue > value){
            minvalue = value;
            mink = k;
        }
    }
    return minvalue;
}

void minmult(int n, vector<int> &d, matrix_t& M, matrix_t& P){
    //d는 값이 변경되지 않음에도 &를 이용해 참조하고 있다.
    //그 이유는 vector 자료구조에서는 복사보다는 참조가 더 적은 비용이 들기 때문이다.
    //만약 &를 사용해 복사를 사용하면 오류가 뜬다.
    for(int i=1; i<=n; i++)
        M[i][i]=0;
    for(int diag =1; diag <=n-1; diag++)
    //diag을 오른쪽 위로 옮겨가며 M[1][n]을 향해감
    //M[1][n]이 최소 곱셈값
        for(int i=1; i<=n-diag; i++){
            int k, j=i+diag;
            M[i][j]=minimum(i, j, k, d, M);
            //k는 minimum을 만드는 중간값으로써 P에 기록됨
            //d는 각 matrix의 행과 열을 나타내는 배열
            P[i][j] = k;
        }
}

void order(int i, int j, matrix_t& P, string& s){
    if(i==j)
        s+=string("(")+string("A")+to_string(i)+string(")");
        //to_string은 <string> 필요
    else{
        int k = P[i][j];
        s += string("(");
        order(i, k, P, s);
        order(k+1, j, P, s);
        s += string(")");
    }
}

void print_uptri(int n, matrix_t A){
    for(int i=1; i<=n; i++){
        cout<< A[i][i];
        for(int j=i+1; j<=n; j++){
            cout<< " "<<A[i][j]; 
        }
        cout<< endl;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> d(n+1);
    for(int i=0; i<=n; i++){
        cin >> d[i];
    }
    matrix_t M(n+1, vector<int>(n+1));
    matrix_t P(n+1, vector<int>(n+1));

    minmult(n, d, M, P);
    print_uptri(n, M);
    print_uptri(n, P);

    cout<< M[1][n]<< endl;

    string s;
    order(1, n, P, s);
    cout << s<< endl;

    return 0;
}