N, S = list(map(int, input().split()))
mp = {}
direction = 1
size = 1
cnt = 0
visited = [0 for i in range(N)]
for i in range(N):
    q, v = list(map(int, input().split()))
    mp[i] = (q, v)

init = S - 1
while init >= 0 and init < N:
    if mp[init][0] and mp[init][1] <= size and not visited[init]:
        cnt += 1
        visited[init] = 1
    elif mp[init][0] == 0:
        direction *= -1
        size += mp[init][1]
    init += direction * size

print(cnt)



