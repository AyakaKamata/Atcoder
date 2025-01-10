N, M = map(int, input().split())
d = [1 for i in range(M + 1)]
for _ in range(N):
    L, R = map(int, input().split())
    d[R] = max(d[R], L + 1)
for r in range(1, M + 1):
    d[r] = max(d[r], d[r - 1])
ans = 0
for r in range(1, M + 1):
    ans += r - d[r] + 1
print(ans)