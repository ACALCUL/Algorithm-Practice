#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> sequence_of_integer;

bool is_feasible(sequence_of_integer& K, sequence_of_integer& deadline){
    for(int i=1; i<K.size(); i++)
        if(i>deadline[K[i]])
            return false;
    return true;
}

void schedule(int n, sequence_of_integer& deadline, sequence_of_integer &J){
    sequence_of_integer K;//K는 가장 profit이 큰 job list을 담는 임시 저장소
    J.clear();
    J.push_back(0);//0은 사용하지 않음
    J.push_back(1);//가중치가 내림차순이므로 일단 1부터 추가
    for(int i=2; i<=n; i++){//i는 insert할 job
        K.resize(J.size());
        copy(J.begin(), J.end(), K.begin());
        int j=1;//j는 job이 들어갈 자리
        while(j<K.size()&&deadline[K[j]]<=deadline[i]){
            //넣을 job인 i의 deadline이 K 원소의 dealine보다 클수록 j++
            //K를 내림차순으로 하기 위함
            j++;
        }
        K.insert(K.begin()+j, i);
        if(is_feasible(K, deadline)){
            J.resize(K.size());
            copy(K.begin(), K.end(), J.begin());
        }//K가 feasible하면 J에다가 K대입

    }
}

int main(){
    int n;
    cin>>n;

    sequence_of_integer deadline(n+1);
    for(int i=1; i<=n; i++){
        cin >> deadline[i];
    }
    sequence_of_integer profit(n+1);
    for(int i=1; i<=n; i++){
        cin >> profit[i];
    }
    sequence_of_integer J;
    schedule(n, deadline, J);

    int sum=0;
    for(int i: J){
        sum+=profit[i];
    }
    cout << sum<<endl;

    cout<<profit[J[1]];
    for(int i=2; i<J.size(); i++){
        cout<<" "<<profit[J[i]];
    }
}
