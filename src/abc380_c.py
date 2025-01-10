import re

N,K=map(int, input().split())
S=list(input())
chunks = re.findall(r'1+|0+', ''.join(S))
cnt=0
for i,chunck in enumerate(chunks):
  if "1" in chunck:
    cnt+=1
    if cnt==K:
      res=i
      break
if res==len(chunks)-1:
  res_s=chunks[:i-1]+[chunks[i]]+[chunks[i-1]]
else:
  res_s=chunks[:i-1]+[chunks[i]]+[chunks[i-1]]+chunks[i+1:]
print("".join(res_s))


