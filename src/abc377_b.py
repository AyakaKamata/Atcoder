S=[list(input()) for _ in range(8)]
li=[0,1,2,3,4,5,6,7]
li2=[0,1,2,3,4,5,6,7]
for i in range(8):
  for j in range(8):
    if S[i][j]=='#':
      if i in li:
        li.remove(i)
      if j in li2:
        li2.remove(j)
print(len(li)*len(li2))