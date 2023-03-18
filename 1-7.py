def fib(n):
    a=0
    b=1
    if n==0 or n==1:
        return n
    for i in range(2, n+1):
        c=a+b
        a=b
        b=c
        #위의 두 코드를 바꾸어써서 논리 오류 발생했음
    return c%1000000

n=int(input())
print(fib(n))
