N,K=map(int,input().split())
S=list(input())
res=0
for i in range(N-K+1):
  flag=0
  for j in range(K):
    if S[i+j]=='O':
      flag+=1
  if flag==K:
    res+=1
    for j in range(K):
      S[i+j]='X'

print(res)
