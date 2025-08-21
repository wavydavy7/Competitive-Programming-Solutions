def cacti_cartography():
    # Breadth-First Search (BFS) function for a single node
    def bfs(u):  
        dist = [-1]*N  # Initialize distances as -1 (unvisited) for all nodes
        dist[u] = d = 0  # Distance to the starting node is 0
        q = [u]  # Queue for BFS, starting with the node u
        while q:  # While there are nodes to process
            d += 1  # Increment distance for the next level of nodes
            new_q = []  # Prepare new queue for the next level
            for u in q:  # For each node in the current level
                for v in adj[u]:  # Check all adjacent nodes
                    if dist[v] != -1:  # If already visited, skip
                        continue
                    dist[v] = d  # Set distance for the node
                    new_q.append(v)  # Add it to the queue for the next level
            q = new_q  # Update queue to the next level
        print("distances: " + str(dist));
        return dist  # Return distances from the node u to all other nodes

    # Iterative Depth-First Search (DFS) function for detecting cycles
    def iter_dfs():  
        idxs, parent, in_cycle, cycles = [-1]*N, [-2]*N, [False]*N, [[] for _ in range(N)]  # Initialize DFS structures
        idx = 0  # Index for DFS order
        stk = [(root, -1)]  # Stack for DFS, starting with the root node
        while stk:  # While there are nodes to process
            u, p = stk.pop()  # Pop a node and its parent from the stack
            if idxs[u] != -1:  # If node is already visited
                if idxs[u] < idxs[p]:  # If it's part of a cycle
                    cycle = []  # Start a new cycle
                    while p != u:  # Trace back the cycle
                        in_cycle[p] = True  # Mark node as part of a cycle
                        cycle.append(p)  # Add node to the cycle
                        p = parent[p]  # Move to the parent
                    cycles[u].append(cycle)  # Add the cycle to the list
                continue
            idxs[u] = idx  # Set DFS index for the node
            idx += 1  # Increment DFS index
            parent[u] = p  # Set parent of the node
            for v in reversed(adj[u]):  # For each adjacent node in reverse order
                if v == p:  # Skip the parent node
                    continue
                stk.append((v, u))  # Add the node and its parent to the stack
        print("idxs: " + str(idxs))
        print("parent: " + str(parent))
        print("in-cycles: " + str(in_cycle))
        print("cycles: " + str(cycles))
        return idxs, parent, in_cycle, cycles  # Return DFS results
    #your cycles includes the parents of stuff in the cycle, so the last point before visited node is not included  
    #in cycles includes everthing but the root of the cycle

    # Read input: number of nodes (N), edges (M), and limit (K)
    N, M, K = list(map(int, input().split()))
    C = list(map(int, input().split()))  # Cost array
    A_B = [list(map(lambda x: int(x)-1, input().split())) for _ in range(M)]  # Edges of the graph
    assert(M <= 3*(N-1)//2)  # Ensure the graph is a cactus graph
    adj = [[] for _ in range(N)]  # Initialize adjacency list
    for u, v in A_B:  # For each edge
        adj[u].append(v)  # Add edge to adjacency list
        adj[v].append(u)  # Add reverse edge for undirected graph
    root = 0  # Set root of the graph
    dist = [bfs(u) for u in range(N)]  # Compute BFS distances from each node
    idxs, parent, in_cycle, cycles = iter_dfs()  # Perform iterative DFS to detect cycles
    order = [-1]*N  # Initialize order array
    for i, x in enumerate(idxs):  # For each node and its DFS index
        order[x] = i  # Set order based on DFS index
    # print("order: " + str(order))
    dp = [[0 if dist[u][v] <= K else INF for v in range(N)] for u in range(N)]  # Initialize DP table with 0-based distances, where only covered vertices are represented by 0s
    # print("dp " + str(dp))

    # Fill DP table considering cycles
    for u in reversed(order):  # For each node in reverse DFS order
        # print(u) #process in reverse order of traversal
        for v in adj[u]:  # For each adjacent node
            if parent[v] != u or in_cycle[v]:  # v must be kid and cannot be in the middle of a cycle(could be the root of cycle)
                continue
            cycles[u].append([v])  # give 'em his own little cycle
            print("cycles[u] " + str(u) + str(cycles[u])) #u is 0-indexed
        for cycle in cycles[u]:  # For each cycle
            print("going through cycles[u]")
            print(cycle)
            dp2 = [[INF]*min(2*K+1, len(cycle)-i) for i in range(len(cycle))]  # Initialize secondary DP table for the cycle, where ith entry represents ith node in cycle... looks like 2k + 1s until end of range hits root again, then ranges gradually become smaller
            print(dp2)
            for v in range(N):  # For each node
                for i in range(len(cycle)):  # For each element in the cycle
                    print("This is the prefix: " + str((v, i)) + " valued at " + str(C[v]))
                    prefix = C[v]  # Start with the cost of the node
                    for l in range(1, len(dp2[i])+1):  # For each possible length in the cycle
                        print("dp cycle of: " + str((i + l - 1, v)) + " is " + str(dp[cycle[i+(l-1)]][v]))  #first comes from element in cycle analyzing, second comes from elsewhere in graph
                        if dp[cycle[i+(l-1)]][v] == INF:  # If the distance is infinite, after looking to the left side, unreachable
                            break  # Stop processing this length
                        prefix += dp[cycle[i+(l-1)]][v]  # Add the cost, from v to the left side, then to i
                        dp2[i][l-1] = min(dp2[i][l-1], prefix)  # Update the secondary DP table with the minimum cost
                        print("using dp2 " + str(dp2[i][l-1]) + " with  " + str((i, l - 1)))
            for v in range(N):  # For each node
                if dp[u][v] == INF:  # If the distance is infinite from the root of the cycle
                    continue  # Skip this node
                dp3 = [INF]*(len(cycle)+1)  # Initialize tertiary DP table for the cycle, including root?
                print("dp3" + str(dp3))
                dp3[0] = dp[u][v]  # Set initial value based on primary DP table
                for i in range(len(cycle)):  # For each element in the cycle
                    print("ith in cycle " + str(i) + " " + str(dp3[i + 1]) + " and " + str(dp3[i]+dp[cycle[i]][v]))
                    dp3[i+1] = min(dp3[i+1], dp3[i]+dp[cycle[i]][v])  # Update tertiary DP table with the minimum cost
                    for l in range(1, min(2*K+1, i+1)+1):  # For each possible length in the cycle
                        print("inner loop update: " + str(dp3[(i+1)-l]+dp2[(i+1)-l][l-1]))
                        dp3[i+1] = min(dp3[i+1], dp3[(i+1)-l]+dp2[(i+1)-l][l-1])  # Update tertiary DP table with the minimum cost considering the secondary DP table
                print("new value for " + str((u, v)) + " is " + str(dp3[-1]))
                dp[u][v] = dp3[-1]  # Update the primary DP table with the final cost
    return min(dp[root][u]+C[u] for u in range(N))  # Return the minimum cost from the root to u, then everything from u plus u

INF = float("inf")  # Define infinity
for case in range(int(input())):  # For each test case
    print('Case #%d: %s' % (case+1, cacti_cartography()))  # Print the case number and the result of the cacti_cartography function
