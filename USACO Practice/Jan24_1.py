# t = int(input())

# def solve():
#     N, Q, C = map(int, input().strip().split())
#     B = [0] * (N + 1)
#     c = [0] + [*map(int, input().strip().split())]
#     assigned = [*map(bool, c)]

#     # Initially choose 1 for every non-fixed element
#     c = [score if score else 1 for score in c]

#     for _ in range(Q):
#         ai, hi = map(int, input().strip().split())
#         B[ai] = hi

#     # Ensure constraints for B
#     for i in range(1, N + 1):
#         # Ensure that every j such that i < j < B[i] has B[j] = B[i]
#         for j in range(i, B[i]):
#             if B[j] != 0 and B[j] != B[i]:
#                 return print(-1)
#             B[j] = B[i]

#     for i in range(1, N + 1):
#         if B[i] == 0:
#             continue
#         # calculate max before and max after
#         mx_before = max(c[: i + 1])
#         mx_after = max(c[: B[i]])

#         # change max before such that mx_before = mx_after, this needs to be the biggest in the range
#         if mx_after > mx_before: #there needs to be something in between that needs to be bigger
#             for j in range(i, 0, -1):
#                 if B[j] != 0 and B[j] < B[i]: #before you get to your one that's getting changed, you need to ensure that after this change,
#                 #the one's in the middle all map to c_i
#                     return print(-1)
#                 if assigned[j]:
#                     continue
#                 c[j] = mx_after 
#                 break
#             else:
#                 return print(-1)
#             mx_before = mx_after

#         if not assigned[B[i]]:
#             c[B[i]] = mx_before + 1
#         # check to make sure B[i] > mx_before
#         if c[B[i]] <= mx_before:
#             return print(-1)

#     # Check that each element in the minimum sequence is at most C
#     for i in range(1, N + 1):
#         if c[i] > C:
#             return print(-1)

#     return print(*c[1:])


# for _ in range(t):
#     solve()

#write the optimization
def solve():
    N, Q, C = map(int, input().split())
    c = [0] + [*map(int, input().split())]
    B = [0] * (N + 1)
    assigned = [*map(bool, c)]

    c = [score if score else 1 for score in c]
    #exploit monotonicity
    for i in range(Q):
        end, final = map(int, input().split())
        B[end] = final

    curind = 1
    # while curind <= N:
    #     i = curind
    #     # Ensure that every j such that i < j < B[i] has B[j] = B[i]
    #     while curind < B[i]:
    #         if B[curind] != 0 and B[curind] != B[i]:
    #             return print(-1)
    #         B[curind] = B[i] #if it's equal to 0, just make sure that it follows the rules
    #         curind += 1
    #     curind = max(curind, i+1)
    
    while curind <= N: 
        i = curind
        while i < B[curind]: #if B[curind] == 0, nothing happens
            if B[i] != 0 and B[i] != B[curind]:
                return print("-1")
            B[i] = B[curind]
            i += 1
        curind = max(curind + 1, i)

    mx_before = 0
    mx_after = 0
    i = 1
    while i <= N:
        # calculate max before and max after
        mx_before = max(mx_before, c[i])
        mx_after = max(mx_after, c[i])
        if B[i] == 0: 
            i += 1
            continue
        mx_after = max(mx_after, *c[i:B[i]])
        
        # change mx_before such that mx_before = mx_after
        if mx_after > mx_before:
            for j in range(i, 0, -1):
                if B[j] != 0 and B[j] < B[i]:
                    return print(-1)
                if assigned[j]:
                    continue
                c[j] = mx_after
                break
            else:
                return print(-1)
            mx_before = mx_after

        if not assigned[B[i]]:
            c[B[i]] = mx_before + 1
        # check to make sure B[i] > mx_before
        if c[B[i]] <= mx_before:
            return print(-1)

        i = B[i]

    # Check that each element in the minimum sequence is at most C
    for i in range(1, N + 1):
        if c[i] > C:
            return print(-1)

    return print(*c[1:])


T = int(input())
while T:
    T -= 1
    solve()
    

