li_=[]
li=[]
for i in range(10):
  S=input()
  if '#' in S:
    li_.append(i+1)
    S_=S
A=min(li_)
B=max(li_)

for j in range(10):
  if S_[j] == '#':
    li.append(j+1)
C=min(li)
D=max(li)
print(A,B)
print(C,D)