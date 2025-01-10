N=int(input())
a=N//100
b=(N-a*100)//10
c=N-a*100-b*10
print((b*100+c*10+a), (c*100+a*10+b))