#include <iostream>
#include <vector>

using namespace std;
int n;
int cnt=0;
vector<int> S;

void mergesort2(int low, int high);
void merge2(int low, int mid, int high); 

void mergesort2(int low, int high) {
    if(low<high){
        int mid= (low+high)/2;
        mergesort2(low, mid);
        mergesort2(mid+1, high);
        merge2(low, mid, high);
    }
}

void merge2(int low, int mid, int high) {
    int i=low, j=mid+1, k=0;
    vector<int> U(high - low + 1);
    while (i <= mid && j <= high) {
        U[k++] = (S[i] < S[j]) ? S[i++] : S[j++];
        cnt++; // S의 원소끼리의 비교 연산 횟수 카운트. cnt는 전역 변수
    }

    if (i > mid)
        while (j <= high) U[k++] = S[j++];
    else
        while (i <= mid) U[k++] = S[i++];
    
    for (int t = low; t <= high; t++)
        S[t] = U[t-low];
}

int main(){
    cin >> n;
    S.push_back(0);
    int a;
    for(int i=1; i<=n; i++){
        cin>>a;
        S.push_back(a);
    }
    mergesort2(1, n);
    cout<< S[1];
    for(int i=2; i<=n; i++ ){
        cout << " "<< S[i];
    }
    cout << endl << cnt<<endl;
}