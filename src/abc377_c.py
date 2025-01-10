N, M = map(int, input().split())
li = [list(map(int, input().split())) for _ in range(M)]
take = [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]
no_li = set(tuple(x) for x in li)
for i in range(M):
  for j in range(8):
    if (1<=li[i][0]+take[j][0]<=N) and (1<=li[i][1]+take[j][1]<=N):
      no_li.add(((li[i][0]+take[j][0]),(li[i][1]+take[j][1])))
print(N**2-len(no_li))