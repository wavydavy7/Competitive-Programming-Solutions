class Pair:
    def __init__(self, f, s):
        self.f = f
        self.s = s

def main():
    #rooted dfs function
    def dfs1(i, p):
        ret = 0
        for next_node in g[i]:
            if next_node != p:
                c = dfs1(next_node, i)
                ret = max(ret, c + 1)
                if c + 1 > maxl1[i].f:
                    maxl2[i] = maxl1[i]
                    maxl1[i] = Pair(c + 1, next_node)
                elif c + 1 > maxl2[i].f:
                    maxl2[i] = Pair(c + 1, next_node)
        return ret
    
    # def dfs(i, p):
    #     ret = 0
    #     for next_node in g[i]:
    #         if next_node != p:
    #             c = dfs1(next_node, i)
    #             ret = max(ret, c + 1)
    #             if c + 1 > maxl1[i].f:
    #                 maxl2[i] = maxl1[i]
    #                 maxl1[i] = Pair(c + 1, next_node)
    #             elif c + 1 > maxl2[i].f:
    #                 maxl2[i] = Pair(c + 1, next_node)
    #     return ret

    #longest chain could be from outside the rooted
    def dfs2(i, p):
        if p != 0:
            if maxl1[p].s == i: #if longest chain passes through x, try the second longest
                if maxl2[p].f + 1 > maxl1[i].f: #you try the second longest + 1
                    maxl2[i] = maxl1[i]
                    maxl1[i] = Pair(maxl2[p].f + 1, p)
                elif maxl2[p].f + 1 > maxl2[i].f:
                    maxl2[i] = Pair(maxl2[p].f + 1, p)
            else: #if it's from outside
                if maxl1[p].f + 1 > maxl1[i].f: #you take the longest from outside ofc and check it against its first and second longest chain
                    maxl2[i] = maxl1[i]
                    maxl1[i] = Pair(maxl1[p].f + 1, p)
                elif maxl1[p].f + 1 > maxl2[i].f:
                    maxl2[i] = Pair(maxl1[p].f + 1, p)
        for next_node in g[i]:
            if next_node != p:
                dfs2(next_node, i)
    
    # def dfs2(i, p):
    #     if p != 0:
    #         if maxl1[p].s == i:
    #             if maxl2[p].f + 1 > maxl1[i].f:
    #                 maxl2[i] = maxl1[i]
    #                 maxl1[i] = Pair(maxl2[p].f + 1, p)
    #             if maxl2[p].f + 1 > maxl2[i].f:
    #                 maxl2[i] = Pair(maxl2[p].f + 1, p)
    #         else:
    #             if maxl1[p].f + 1 > maxl1[i].f:
    #                 maxl2[i] = maxl1[i]
    #                 maxl1[i] = Pair(maxl1[p].f + 1, p)
    #             if maxl1[p].f + 1 > maxl2[p].f:
    #                 maxl2[p] = Pair(maxl1[p].f + 1, p)
    #     for next_node in g[i]:
    #         if next_node != p:
    #             dfs2(next_node, i)


    N = int(input())
    g = [[] for _ in range(N + 1)] 
    maxl1 = [Pair(0, 0) for _ in range(N + 1)]  # Remove the 'g' from maxl1 and maxl2 declarations
    maxl2 = [Pair(0, 0) for _ in range(N + 1)] #you have this to calculate the distance between node in the max chain and the longest one
    #outside the node(which is obv the second longest)

    for i in range(1, N):
        a, b = map(int, input().split())
        g[a].append(b)
        g[b].append(a)
    dfs1(1, 0)
    dfs2(1, 0)

    for i in range(1, N + 1):
        print(maxl1[i].f)

main()
