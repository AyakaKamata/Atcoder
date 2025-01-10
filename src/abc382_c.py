import bisect

N, M = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

A_with_index = sorted((a, i) for i, a in enumerate(A))
A_index = [a[1] for a in A_with_index]

cumulative_min = [0] * N
cumulative_min[0] = A_index[0]
for i in range(1, N):
    cumulative_min[i] = min(cumulative_min[i - 1], A_index[i])

res = [-1] * M

for i in range(M):
    idx = bisect.bisect_right([a[0] for a in A_with_index], B[i]) - 1
    if idx >= 0:
        res[i] = cumulative_min[idx] + 1

for r in res:
    print(r)

