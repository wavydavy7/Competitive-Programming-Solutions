def cacti_cartography():
    def bfs(u):  # Time: O(M)
        dist = [-1]*N
        dist[u] = d = 0
        q = [u]
        while q:
            d += 1
            new_q = []
            for u in q:
                for v in adj[u]:
                    if dist[v] != -1:
                        continue
                    dist[v] = d
                    new_q.append(v)
            q = new_q
        return dist

    def iter_dfs():  # Time: O(M)
        idxs, parent, in_cycle, cycles = [-1]*N, [-2]*N, [False]*N, [[] for _ in range(N)]
        idx = 0
        stk = [(root, -1)]
        while stk:
            u, p = stk.pop()
            if idxs[u] != -1:
                if idxs[u] < idxs[p]:
                    cycle = []
                    while p != u:
                        in_cycle[p] = True
                        cycle.append(p)
                        p = parent[p]
                    cycles[u].append(cycle)
                continue
            idxs[u] = idx
            idx += 1
            parent[u] = p
            for v in reversed(adj[u]):
                if v == p:
                    continue
                stk.append((v, u))
        return idxs, parent, in_cycle, cycles

    N, M, K = list(map(int, input().split()))
    C = list(map(int, input().split()))
    A_B = [list(map(lambda x: int(x)-1, input().split())) for _ in range(M)]
    assert(M <= 3*(N-1)//2)  # cactus graph, see https://mathoverflow.net/questions/425622/the-upper-bound-of-edges-of-the-generalized-cactus-graphs
    adj = [[] for _ in range(N)]
    for u, v in A_B:
        adj[u].append(v)
        adj[v].append(u)
    root = 0
    dist = [bfs(u) for u in range(N)]
    idxs, parent, in_cycle, cycles = iter_dfs()
    order = [-1]*N
    for i, x in enumerate(idxs):
        order[x] = i
    dp = [[0 if dist[u][v] <= K else INF for v in range(N)] for u in range(N)]
    for u in reversed(order):
        for v in adj[u]:  # Total Time: O(N * M)
            if parent[v] != u or in_cycle[v]:
                continue
            cycles[u].append([v])
        print(cycles[u])
        for cycle in cycles[u]:  # Total Time: O(N^2 * min(K, L))
            dp2 = [[INF]*min(2*K+1, len(cycle)-i) for i in range(len(cycle))]
            print(dp2)
            for v in range(N):
                for i in range(len(cycle)):
                    prefix = C[v]
                    for l in range(1, len(dp2[i])+1):
                        if dp[cycle[i+(l-1)]][v] == INF:
                            break
                        prefix += dp[cycle[i+(l-1)]][v]
                        dp2[i][l-1] = min(dp2[i][l-1], prefix)
            print(dp2)
            for v in range(N):
                if dp[u][v] == INF:
                    continue
                dp3 = [INF]*(len(cycle)+1)
                dp3[0] = dp[u][v]
                for i in range(len(cycle)):
                    dp3[i+1] = min(dp3[i+1], dp3[i]+dp[cycle[i]][v])
                    for l in range(1, min(2*K+1, i+1)+1):
                        dp3[i+1] = min(dp3[i+1], dp3[(i+1)-l]+dp2[(i+1)-l][l-1])
                dp[u][v] = dp3[-1]
            print(dp3)
    return min(dp[root][u]+C[u] for u in range(N))

INF = float("inf")
for case in range(int(input())):
    print('Case #%d: %s' % (case+1, cacti_cartography()))