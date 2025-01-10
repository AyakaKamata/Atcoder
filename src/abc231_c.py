from bisect import bisect_left

N, Q = map(int, input().split())
A = sorted(map(int, input().split()))
x = [int(input()) for _ in range(Q)]

for i in range(Q):
    print(N - bisect_left(A, x[i]))
