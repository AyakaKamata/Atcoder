# 入力
n = int(input())
cards = []
for i in range(n):
    a, c = map(int, input().split())
    cards.append((a, c, i))

# C[i] の昇順にソート
cards.sort(key=lambda card: card[1])

# 答えを求める計算
ans = []
v = 0
for card in cards:
    if card[0] > v:
        v = card[0]
        ans.append(card[2])

# 答えをソート
ans.sort()

# 出力
m = len(ans)
print(m)
print(" ".join(str(index + 1) for index in ans))
