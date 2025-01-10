N = int(input())
Q = list(map(int, input().split()))
A = list(map(int, input().split()))
B = list(map(int, input().split()))

ans = 0
y= float('inf')
for x in range(max(Q) + 1):
    flag = 0
    for i in range(N):
        if Q[i] < A[i] * x:
            flag = 1
            break
        elif B[i] > 0:
            y = min(y, (Q[i] - A[i] * x) // B[i])
    if flag != 1:
	    ans = max(ans, x + y)
print(ans)

