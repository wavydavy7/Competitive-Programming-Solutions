def compress(items):
    # Properly compress consecutive duplicates
    res = []
    for index, c in enumerate(items):
        if not res or res[-1] != int(c):
            res.append(int(c))
    return res

def solve(arr1, arr2):
    res = []
    
    # print(arr1)
    # print(arr2)
    if len(arr1) > 1 and len(arr2) > 1 and arr1[-1] == arr2[-1]:
        res.append((1, 2))
        arr2.pop()
    
    val = arr1[-1] if len(arr1) > 1 else None
    which = arr1 if arr2[0] != val else arr1 
    other = arr1 if which is arr2 else arr2
    which_stack = 2 if which is arr2 else 1
    flag = False
    which = which[1:]
    other = other[1:]
    
    if not which:
        temp = which
        which = other
        other = temp
        which_stack = 3 - which_stack
    # print(which)
    # print(other)
    for e in which[::-1]:
        res.append((which_stack, 3 if e == val else 3 - which_stack))
        flag = True
    for o in other[::-1]: 
        res.append((3 - which_stack, 3 if o == val else which_stack))

    if flag and len(which) > 1:
        res.append((3, which_stack));
    return res

T = int(input())

while T > 0:
    T -= 1
    N, P = map(int, input().split())
    tube1 = compress(input())
    tube2 = compress(input())
   
    
    #one on first, two on bottom
    if tube1[0] == tube2[0]:
        tube1.insert(0, 3 - tube2[0])
    M = len(tube1) + len(tube2) - 2
    if M > 1:
        M += 1
    print(M)

    if P == 2 or P == 3:
        output = solve(tube1, tube2)
        
        for fr, to in output:
            print(f"{fr} {to}")
    




    









