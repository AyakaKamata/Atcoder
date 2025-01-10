N,D=map(int,input().split())
S=input()
index=[]
for i in range(N):
  if S[i]=="@":
    index.append(i)
index.sort(reverse=True)
res=["."]*N
for i in index[D:]:
  res[i]="@"
print("".join(res))