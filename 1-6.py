global cnt
cnt=0

def fib(n):
    global cnt
    cnt+=1
    if n<=1:
        return n
    else:
        return (fib(n-1)+fib(n-2))%1000000

n=int(input())
print(fib(n))
print(cnt)
