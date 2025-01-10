N=int(input())
A=[input() for _ in range(N)]
for i in range(N-1):
  for j in range((i+1), N):

    if A[i][j] == 'D' and not(A[j][i] == 'D'):
      print('incorrect')
      exit()
    elif A[i][j] == 'L' and not(A[j][i] == 'W'):
      print('incorrect')
      exit()
    elif A[i][j] == 'W' and not(A[j][i] == 'L'):
      print('incorrect')
      exit()
print('correct')

