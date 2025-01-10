N,D=map(int,input().split())
S=input()
cnt=0
for i in range(N):
  if S[i]=='.':
    cnt+=1

print(cnt+D)