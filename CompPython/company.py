#finished

def LCA(a, b):
    if depth[a] < depth[b]:
        a, b = b, a
    a = jump(a, depth[a] - depth[b])
    if a == b:
        return a

    for i in range(19, -1, -1):
        aT = up[a][i]
        bT = up[b][i]
        if aT != bT:
            a = aT
            b = bT

    return up[a][0]

N, Q = map(int, input().split())
depth = [0] * 200005
up = [[0] * 20 for _ in range(200005)]
adj = [[] for _ in range(200005)]

def dfs(v):
    
    for i in range(1, 20):
        up[v][i] = up[up[v][i - 1]][i - 1]
    
    for x in adj[v]:
        if x != up[v][0]:
            depth[x] = depth[v] + 1
            up[x][0] = v
            dfs(x)

def jump(x, d):
    for i in range(20):
        if (d >> i) & 1:
            x = up[x][i]
    return x

edges = list(map(int, input().split()))
for i in range(1, N):
    b = edges[i - 1] - 1
    adj[b].append(i)

up[0][0] = 0
depth[0] = 0
dfs(0)

for _ in range(Q):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    print(LCA(a, b) + 1)  # Add +1 to the output to match the expected format
