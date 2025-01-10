S=list(input())
res=[]
cnt=0
for i in range(len(S)):
  if S[i]=='|':
    res.append(cnt)
    cnt=0
  else:
    cnt+=1
print(*res[1:])