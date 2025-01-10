from itertools import combinations

N, M = map(int, input().split())
ans = []
for c in combinations(list(range(1, M - 9 * (N - 1) + 1)), N):
    l = list(c)
    for i in range(1, N):
        l[i] += 9 * i
    ans.append(l)
print(len(ans))
for i in ans:
    print(*i)

