#include <iostream>
#include <vector>
using namespace std;

int bin2(int n, int k){
    vector<int> B(n+1, 0);//n+1까지 선언해야 n행이 생김
    vector<int> B2(n+1, 0);
    B[0]=1;
    B2[0]=1;
    for(int i=1; i<=n; i++){
        //i는 파스칼의 삼각형의 행을 나타냄
        for(int j=1; j<=i; j++){
            //j는 파스칼의 삼각형의 열을 나타냄
            B2[j]=(B[j-1]+B[j])%10007;
        }

        /* cout << "i : "<< i << endl;
        for(int m: B2){
            cout << m << " ";
        }
        cout << endl<< endl; */

        copy(B2.begin(), B2.begin()+i+1,  B.begin());
        //copy에서 두번쨰 인자의 주솟값은 포함안하므로 (begin+i)가 아니라 (begin+i+1)이 맞음

        /* for(int m: B){
            cout << m << " ";
        }
        cout << endl<< endl; */
    }

    return B[k];
}

int main(){
    int n, k;
    cin >> n >> k;
    cout << bin2(n, k);
    return 0;
}