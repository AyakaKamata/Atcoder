from math import ceil

S=input()
Q=int(input())
K=list(map(int, input().split()))

res=[]
for i in range(Q):
  st=S[(K[i]-1)%len(S)]
  if bin((K[i] + len(S) - 1) // len(S)-1).count("1") % 2 == 1:
    st = st.swapcase()
  res.append(st)
print(*res)
