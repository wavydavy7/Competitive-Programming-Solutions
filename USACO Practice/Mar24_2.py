# from collections import defaultdict
# import bisect
# N, P = map(int, input().split())
# mapx = defaultdict(list)
# mapy = defaultdict(list)

# for i in range(P):
#     x, y = map(int, input().split())
#     mapx[x].append(y)
#     mapy[y].append(x)

# for k in mapx.keys():
#     mapx[k].sort()

# for k2 in mapy.keys():
#     mapy[k2].sort()

# intervals = []
# from_root = {}

# directions = [0, 1, 2, 3] #make it up, left, down, right


# def findDistance(x1, y1, x2, y2):
#     return abs(x1 - x2) + abs(y1 - y2)

# def findLeft(x, y):
#     lst = mapy[y]
#     res = bisect.bisect_left(lst, x)
#     return (lst[res - 1], y) if res != 0 else (-1, -1)

# def findRight(x, y):
#     lst = mapy[y]
#     res = bisect.bisect_right(lst, x)
#     return (lst[res], y) if res != len(mapy[y]) else (-1, -1)

# def findUp(x, y):
#     lst = mapx[x]
#     res = bisect.bisect_right(lst, y)
#     return (x, lst[res]) if res != len(mapx[x]) else (-1, -1)

# def findDown(x, y):
#     lst = mapx[x]
#     res = bisect.bisect_left(lst, y)
#     return (x, lst[res - 1]) if res != 0 else (-1, -1)


# def findNext(x, y, direction, dist):
#     if direction == 0:#up

#         if findLeft(x, y) != (-1, -1):
#             x2, y2 = findLeft(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (1, (x2, y2), dist)#direction, point
#         elif findDown(x, y) != (-1, -1):
#             x2, y2 = findDown(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (2, (x2, y2), dist)#direction, point
#         elif findRight(x, y) != (-1, -1):
#             x2, y2 = findRight(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (3, (x2, y2), dist)#direction, point
        
#     elif direction == 1: #left 
        
#         if findDown(x, y) != (-1, -1):
#             x2, y2 = findDown(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (2, (x2, y2), dist)#direction, point
#         elif findRight(x, y) != (-1, -1):
#             x2, y2 = findRight(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (3, (x2, y2), dist)#direction, point
#         elif findUp(x, y) != (-1, -1):
#             x2, y2 = findUp(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (0, (x2, y2), dist)#direction, point
    
#     elif direction == 2:#down
        
#         if findRight(x, y) != (-1, -1):
#             x2, y2 = findRight(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (3, (x2, y2), dist)#direction, point
#         elif findUp(x, y) != (-1, -1):
#             x2, y2 = findUp(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (0, (x2, y2), dist)#direction, point
#         elif findLeft(x, y) != (-1, -1):
#             x2, y2 = findLeft(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (1, (x2, y2), dist)#direction, point
    
#     elif direction == 3: #right
#         if findUp(x, y) != (-1, -1):
#             x2, y2 = findUp(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (0, (x2, y2), dist)#direction, point
#         elif findLeft(x, y) != (-1, -1):
#             x2, y2 = findLeft(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (1, (x2, y2), dist)#direction, point
#         elif findDown(x, y) != (-1, -1):
#             x2, y2 = findDown(x, y)
#             dist += findDistance(x, y, x2, y2)
#             from_root[(x2, y2)] = dist
#             return (2, (x2, y2), dist)#direction, point
    

# root = min(mapx.keys()), min(mapx[min(mapx.keys())]) #min x and corr y
# start = 0

# curx, cury = root
# dist = 0
# while findNext(curx, cury) != root:
#     dir, (curx, cury), d = findNext(curx, cury)
#     dist = d

# #how far is loop
# findNext(curx, cury)

# def closestOne(x, y):


# for intervals in range(N):
#     x1, y1, x2, y2 = list(map(int, input().split()))
#     #I want the distance from 
#     big = max(from_root[(x1, y1)], from_root[(x2, y2)])
#     small = min(from_root[(x1, y1)], from_root[(x2, y2)])
#     gap = big - small
#     if gap <= dist // 2:
#         intervals.append((small, big))
#     else:
#         intervals.append(0, small)
#         intervals.append(big, dist)
#     #...

# #sweep line
# intervals.sort()
# posts = [0] * P
# active = 0
# for beg, end in intervals: 

from collections import deque

n, k = map(int, input().split())
s = input()
t = input()

d = deque()

ans = 0
for i in range(n):
    if d and d[0][0] < i:
        dist, which = d.popleft()
        ans += abs(which)
        d.append((dist + k, which))
    
    if s[i] != t[i]:
        type = 1 if s[i] == "1" else -1
        if not d or abs(d[0][1] + type) > abs(d[0][1]):
            if not d or d[0][0] != i:
                d.appendleft((i, 0))
            d[0] = d[0][0], d[0][1] + type 

        else: 
            d[0] = d[0][0], d[0][1] + type 
            if d[0][1] == 0:
                d.popleft()
print(ans)


            

        
        







