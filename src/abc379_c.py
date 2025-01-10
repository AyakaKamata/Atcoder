n,m = map(int, input().split())
x = list(map(int, input().split()))
a = list(map(int, input().split()))
xa = []
for _ in x:
    xa.append([_, 0])
for i in range(m):
    j=a[i]
    xa[i][1] = j

if sum(a)!=n:
  print(-1)
  exit()
else:
  sum_ = 0
  sum_idx = 0
  xa.sort()
  for i in range(m):
      if sum_ < xa[i][0] - 1:
          print(-1)
          exit()
      sum_ += xa[i][1]
      sum_idx += xa[i][1] * xa[i][0]
  print(n*(n+1)//2-sum_idx)
