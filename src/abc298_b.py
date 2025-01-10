N=int(input())
A=[list(map(int,input().split())) for _ in range(N)]
B=[list(map(int,input().split())) for _ in range(N)]

for j in range(4):
  flag=0
  for i in range(N):
    a = int(''.join(map(str, A[i])), 2)
    b = int(''.join(map(str, B[i])), 2)
    c = bin(a & b)[2:].zfill(N)
    if bin(a)[2:].zfill(N)!=c:
      break
    else:
      flag+=1
  if flag==N:
    break
  else:
    A=[list(row) for row in zip(*A[::-1])]

if flag==N:
  print('Yes')
else:
  print('No')