N=int(input())
import sys
input = sys.stdin.read
data = input().split()
A = [int(data[i]) for i in range(4*N-1)]
li=[0]*N
for i in range(4*N-1):
  li[A[i]-1]+=1
print(li.index(3)+1)
