#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> LargeInteger;
int threshold=1;
int cnt=0;

void remove_leading_zeros(LargeInteger& v) {
    while (v.size() != 0 && v.back()==0)
        v.pop_back();
}

 void roundup_carry(LargeInteger& v) {
    int carry = 0;
    for (int i =0; i<v.size(); i++){
        v[i]+=carry;
        carry = v[i]/10;
        v[i]=v[i]%10;
    }
    if(carry != 0)
    v.push_back(carry);
 }

 void ladd(LargeInteger a, LargeInteger b, LargeInteger& c){
    c.resize(max(a.size(), b.size()));
    fill(c.begin(), c.end(), 0);
    for(int i =0; i<c.size(); i++){
        if(i< a.size()) c[i] += a[i];
        if(i< b.size()) c[i] += b[i];
    }
    roundup_carry(c);
 }

void lmult(LargeInteger a, LargeInteger b, LargeInteger& c){
    c.resize(a.size()+ b.size()-1);
    fill(c.begin(), c.end(), 0);
    for(int i=0; i<a.size(); i++)
        for(int j=0; j<b.size(); j++)
            c[i+j]+=a[i]*b[j];
    roundup_carry(c);
}

void pow_by_exp(LargeInteger u, int m, LargeInteger &v){
    if (u.size() == 0)
        v.resize(0);
    else{
        v.resize(u.size()+m);
        fill(v.begin(), v.end(), 0);
        copy(u.begin(), u.end(), v.begin()+m);
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &v){
    if(u.size()==0)
        v.resize(0);
    else{
        int k=m <u.size() ? m: u.size();//더 작은 쪽 고르기
        v.resize(k);
        copy(u.begin(), u.begin()+k, v.begin());
        remove_leading_zeros(v);
    }
}

//div_by_exp 만들기(rem_by_exp 응용)

void div_by_exp(LargeInteger u, int m, LargeInteger &v){
    if(u.size()==0)
        v.resize(0);
    else if(u.size()<m)//u < 10^m 인 경우
        v.resize(0);  
    else{//u > 10^m 인 경우
        int k=u.size()-m;
        v.resize(k);
        copy(u.begin()+m, u.end(), v.begin());
        remove_leading_zeros(v);
    }
}

void prod(LargeInteger u, LargeInteger v, LargeInteger &r){
    cnt++;
    LargeInteger x,y,w,z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    int n= max(u.size(), v.size());
    if(u.size()==0||v.size()==0)
        r.resize(0);
    else if(n<=threshold)
        lmult(u, v, r);
    else{
        int m= n/2;
        div_by_exp(u, m, x); rem_by_exp(u, m, y);
        div_by_exp(v, m, w); rem_by_exp(v, m, z);

        prod(x, w, t1); pow_by_exp(t1, 2*m, t2);
        // t1 = x X w; 
        // t2 = t1 X 10^2m = xw * 10^2m;
        prod(x, z, t3); prod(w,y,t4);
        // t3 = x X z; 
        // t4 = w X y; 
        ladd(t3, t4, t5); pow_by_exp(t5, m, t6);
        // t5 = t3 + t4 = xz + wy;
        // t6 = t5 X 10^m= (xz + wy) X 10^m;
        prod(y,z,t7); ladd(t2, t6, t8); ladd(t8, t7, r);
        // t7 = y X z;
        // t8 = t2 + t6 = xw * 10^2m + (xz + wy) X 10^m;
        // r = t7 + t8 = xw * 10^2m + (xz + wy) X 10^m + y X z;
    }
}

/* void __int64_to_LargeInteger(int a, LargeInteger& A){
    __int64 num=a;
    int digit = 0;
    while(num!=0){
        num = num / 10;
        digit++;
    }
    A.resize(digit);

    num=a;
    digit=0;
    while(num!=0){
        A[digit]=num%10;
        num = num / 10;
        digit++;
    }
} */
//__int64 범위를 넘는 숫자가 있을시에 사용불가->문자열을 LargeInteger로 바꾸는 함수 만들기

void string_to_LargeInteger(string a, LargeInteger& A){
    int size=a.size();
    A.resize(size);
    int digit=size, num;
    for (char c : a) {
        if (isdigit(c)) {   
            num = c - '0';   
            A[--digit]=num;
        }
    }
}

void print_LargeInteger(LargeInteger A){
    for(int i=A.size()-1; i>=0; i--){
        cout << A[i];
    }
    cout<<endl;
}

int main(){
    cin >> threshold;
    string a, b;
    cin >> a;
    cin >> b;
    //cout << a<<" "<< b<<endl;

    LargeInteger A, B;
    string_to_LargeInteger(a, A);
    string_to_LargeInteger(b, B);
    /* print_LargeInteger(A);
    print_LargeInteger(B); */
    
    LargeInteger C;
    prod(A, B, C);

    cout << cnt<< endl;
    print_LargeInteger(C);

    return 0;
}