Q=int(input())
q=[list(map(int,input().split())) for i in range(Q)]
d = {}
id_list=list()
for i in range(Q):
  if q[i][0]==1:
    idx = len(d)
    id_list.append(idx)
    d[idx]=0
  elif q[i][0]==2:
    for j in id_list:
      d[j]+=q[i][1]
  else:
    count = sum(1 for v in d.values() if v >= q[i][1])
    print(count)
    d = {k: v for k, v in d.items() if v < q[i][1]}
    d = {new_k: v for new_k, (old_k, v) in enumerate(d.items())}
    id_list = [j for j in id_list if j in d]