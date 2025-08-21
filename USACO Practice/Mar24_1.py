# from collections import defaultdict
# import heapq


# cows, farmers = map(int, input().split()) 
# order = list(map(int, input().split()))

# adj = defaultdict(list)  

# inter = [(0, i + 1) for i in range(farmers)]
# heapq.heapify(inter)
# which = 0
# while which < len(order):
#     amt, farmer = heapq.heappop(inter) 
#     upd = amt + order[which]
#     which += 1
#     heapq.heappush(inter, (upd, farmer)) 
#     while inter and amt != 0 and inter[0][0] == amt:  
#         amt2, farmer2 = heapq.heappop(inter)
#         amt2 += order[which]
#         adj[farmer].append(farmer2)
#         adj[farmer2].append(farmer)
#         which += 1
#         heapq.heappush(inter, (amt2, farmer2)) 
# final, start = heapq.heappop(inter) 

# res = [0] * farmers

# def dfs(v, par):
#     res[v - 1] = 1
#     for nei in adj[v]:
#         if nei != par:
#             dfs(nei, v)

# print(final)
# dfs(start, -1)

# print("".join(map(str, res)))
# import heapq

# cows, farmers = map(int, input().split())
# order = list(map(int, input().split()))

# # Initialize adj as a regular dictionary and manually handle missing keys
# adj = {}

# inter = [(0, i + 1) for i in range(farmers)]
# heapq.heapify(inter)
# which = 0
# length = len(order)
# while which < length:
#     amt, farmer = heapq.heappop(inter)
#     upd = amt + order[which]
#     which += 1
#     heapq.heappush(inter, (upd, farmer))
#     while inter and amt != 0 and inter[0][0] == amt:
#         amt2, farmer2 = heapq.heappop(inter)
#         if which < len(order): # Check to prevent index error
#             amt2 += order[which]
#             # Check if farmer exists in adj, if not initialize with an empty list
#             if farmer not in adj:
#                 adj[farmer] = []
#             if farmer2 not in adj:
#                 adj[farmer2] = []
#             adj[farmer].append(farmer2)
#             adj[farmer2].append(farmer)
#             which += 1
#             heapq.heappush(inter, (amt2, farmer2))
# final, start = heapq.heappop(inter)

# res = [0] * farmers

# def dfs(v, par):
#     res[v - 1] = 1
#     # Check if v exists in adj to avoid KeyError
#     if v in adj:
#         for nei in adj[v]:
#             if nei != par:
#                 dfs(nei, v)

# print(final)
# dfs(start, -1)

# print("".join(map(str, res)))

import heapq

def dfs(v, adj, res, par=-1):
    res[v - 1] = 1
    for nei in adj.get(v, []):  # Use .get() to simplify neighbor iteration
        if nei != par:
            dfs(nei, adj, res, v)

def main():
    cows, farmers = map(int, input().split())
    order = list(map(int, input().split()))

    # Use a list of sets for adjacency to avoid duplicate edges
    adj = {i: set() for i in range(1, farmers + 1)}

    inter = [(0, i + 1) for i in range(farmers)]
    heapq.heapify(inter)
    which = 0
    length = len(order)
    while which < length:
        amt, farmer = heapq.heappop(inter)
        upd = amt + order[which]
        which += 1
        heapq.heappush(inter, (upd, farmer))
        while inter and amt != 0 and inter[0][0] == amt:
            if which < length:  # Use cached length
                amt2, farmer2 = heapq.heappop(inter)
                amt2 += order[which]
                adj[farmer].add(farmer2)  # Add to set, automatically handling duplicates
                adj[farmer2].add(farmer)
                which += 1
                heapq.heappush(inter, (amt2, farmer2))

    final, start = heapq.heappop(inter)
    res = [0] * farmers

    dfs(start, adj, res)  # Pass adj and res as arguments to avoid global dependency

    print(final)
    print("".join(map(str, res)))

if __name__ == "__main__":
    main()


