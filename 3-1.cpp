#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
using namespace std;

int n, x, cnt;//x는 s_list에 있는 원소
vector<int> lst;

int binsearch(int low, int high){
    cnt++;
    int mid;
    if(low>high){
        return -1;
    }
    else{
        mid=(low+high)/2;
        if(x==lst[mid])
            return mid;
        else if(x<lst[mid])
            return binsearch(low, mid-1);
        else
            return binsearch(mid+1, high);
    }
}

int main(){
    int m;
    scanf("%d %d", &n, &m);
    vector<int> s_lst;
    int a;
    for (int i = 0; i < n; i++){
        cin >> a;
        lst.push_back(a);
    }
    //printf("%d\n", m);
    
    for (int i = 0; i < m; i++){
        cin >> a;
        s_lst.push_back(a);
    }
    sort(lst.begin(), lst.end());
    /* for(int i=0; i<n; i++){
        cout<< lst[i] << " ";
    } */ 
    /* for (int i = 0; i < m; i++){
        cout<< s_lst[i] << " ";
    } */
    /* for( auto i=s_lst.begin(); i != s_lst.end(); i++)
        cout << *i << " "; */
    for( auto i=s_lst.begin(); i != s_lst.end(); i++){
        x=*i;
        cnt=0;
        binsearch(0, n-1);
        cout << cnt;
        cout << " "<<binsearch(0,n-1)+1<<endl;
        //문제에서는 배열의 인덱스가 1~n까지 있지만 메모리를 아끼기 위해 배열의 인덱스를 0~n까지 지정했으므로 위 코드로 조정함  
        //cout << x <<endl; 
        }
}