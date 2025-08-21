ALPHABET = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
results = []
t = int(input())
for _ in range(t):
    before = input()
    after = input()

    becomes = {}  # Representing directed graph
    possible = True
    
    # Step 1: Build the graph
    for i in range(len(before)):
        if before[i] in becomes and becomes[before[i]] != after[i]:
            possible = False
            break
        becomes[before[i]] = after[i]
        
    if len(set(after)) == 52 and before != after:
        possible = False

    # Step 2: Check if transformation is possible
    if not possible:
        results.append(-1)
        continue
    
    # Step 3: Count edges and cycles
    answer = 0
    in_degree = {}  # To help detect cycles
    for r in ALPHABET:
        if r in becomes and becomes[r] != r:
            in_degree[becomes[r]] = in_degree.get(becomes[r], 0) + 1
            answer += 1

    seen = {}  # To track visited nodes
    for r in ALPHABET:
        if r not in seen:
            a = r
            while a not in seen:
                seen[a] = r
                a = becomes.get(a, a)
            if a in becomes and a != becomes[a] and seen[a] == r:
                s = a
                cycle = True
                while True:
                    seen[a] = 'moo'
                    if in_degree.get(a, 0) > 1:
                        cycle = False
                    a = becomes[a]
                    if a == s:
                        break
                if cycle:
                    answer += 1
                    
    results.append(answer)

for res in results:
    print(res)
