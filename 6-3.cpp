#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<int>> matrix_t;

pair<matrix_t, matrix_t> lcs(string& x, string& y) {
    x = " " + x;
    y = " " + y;
    //행 또는 열이 0일때는 0으로 만들기 위해 x, y 변경
    int m = x.length();
    int n = y.length();
    matrix_t c(m, vector<int>(n, 0));
    matrix_t b(m, vector<int>(n, 0));
    //c, b에서 행 또는 열이 0일때는 값이 0
    //c는 공통 서열 개수를 담는 배열
    //b는 c가 어느방향으로 진행되었는지 담는 배열(공통서열 출력을 위한 배열)
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (x[i] == y[j]) {
                //공통 서열일 경우
                c[i][j] = c[i - 1][j - 1] + 1;
                //1 추가 하는 이유는 공통서열 추가되었으므로
                b[i][j] = 1;
                //b가 1일 경우 왼쪽 위 값에 영향 받음
            } else {
                //공통 서열 아닐 경우
                //왼쪽 또는 위쪽에서 최댓값 받아오기
                if (c[i][j - 1] > c[i - 1][j]) {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = 2;
                    //b가 2일 경우 왼쪽값에 영향 받음
                } else {
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 3;
                    //b가 3일 경우 위쪽값에 영향 받음
                }
            }
        }
    }
    return make_pair(c, b);
}


string get_lcs(int i, int j, matrix_t& b, string& x) {
    //공통서열이므로 x만 가져와도 충분함
    if (i == 0 || j == 0) {
        return "";
    } else {
        if (b[i][j] == 1) {
            return get_lcs(i - 1, j - 1, b, x) + x[i];
            //1일때 공통서열이므로 x[i]추가
        } else if (b[i][j] == 2) {
            return get_lcs(i, j - 1, b, x);
        } else if (b[i][j] == 3) {
            return get_lcs(i - 1, j, b, x);
        }
    }
}

void print_matrix(int m, int n, matrix_t& A){
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            cout << A[i][j];
        }
        cout<<endl;
    }
}

int main(){
    string x, y;
    cin >> x;
    cin >> y;
    
    pair<matrix_t, matrix_t> lcs_result = lcs(x,y);
    //x, y앞에 공백 붙음
    
    matrix_t c= lcs_result.first;
    matrix_t b= lcs_result.second;

    int m=x.length();
    int n=y.length();
    //cout<< m<<" "<< n<<endl;

    //print_matrix(m-1,n-1, c);
    //print_matrix(m-1,n-1, b);

    cout<<c[m-1][n-1]<<endl;
    string lcs = get_lcs(m-1, n-1, b, x);
    cout<<lcs;
    
    return 0;
}
