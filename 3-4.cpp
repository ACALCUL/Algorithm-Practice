#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cnt=0;
int n;
vector<int> S;

void quicksort(int low, int high);
void partition(int low, int high, int& pivotpoint);

void quicksort(int low, int high){
    int pivotpoint;

    if(low<high){
        partition(low, high, pivotpoint);
        quicksort(low, pivotpoint-1);
        quicksort(pivotpoint +1, high);
    }
}

void partition(int low, int high, int& pivotpoint) {
    int i, j, pivotitem;

    pivotitem = S[low];
    j = low;
    for (i = low+1; i <= high; i++) {
        if (S[i] < pivotitem) {
            j++;
            swap(S[i], S[j]);
            cnt++; // swap 연산의 실행 횟수 카운트
        }
    }
    pivotpoint = j;
    swap(S[low], S[pivotpoint]);
    cnt++; // swap 연산의 실행 횟수 카운트
}

int main(){
    cin >> n;

    S.push_back(0);
    int a;
    for(int i=1; i<=n; i++){
        cin >> a;
        S.push_back(a);
    }
    //input
    quicksort(1, n);//sort
    cout<< S[1];
    for(int i=2; i<=n; i++){
        cout << " "<< S[i];
    }
    //output
    cout << endl<< cnt;

}