def multiSplit(s, delim):
    ret = [[]]
    # Construct a trie for all delimiters.
    trie = {}
    for d in delim:
        ptr = trie
        for ch in d:
            if ch not in ptr:
                ptr[ch] = {}
            ptr = ptr[ch]
        ptr[None] = len(d)  # Mark the end of a delimiter with its length.
    print(trie)

    # Initialize a list to keep track of potential substrings.
    ptrs = []
    for i, ch in enumerate(s):
        ret[-1].append((ch, i))  
        print("ret[-1]")
        print(ret[-1])
        ptrs.append(trie)  #crucial, you add beginning ptr for overlaps
        print("ptrs")
        print(ptrs)
        new = []
        for ptr in ptrs:
            if ch not in ptr:
                continue  
            print("Didn't continue")
            print(ptr)
            ptr = ptr[ch]  #new includes all of the ones you get after moving a char
            new.append(ptr)  
        
            print("new")
            print(new)

            if None not in ptr:
                continue  
            #if you can start removing, do it to that index
            removeLimit = i - ptr[None] + 1
            print("removeLimit")
            print(removeLimit)
            
            #if it's the empty [], just remove it
            while len(ret) > 0 and (len(ret[-1]) == 0 or ret[-1][-1][1] >= removeLimit):
                print("in loop!")
                if not ret[-1]:
                    ret.pop() 
                else:
                    ret[-1].pop()  
            print("after while")
            print(ret)
           
            ret.append([])

        ptrs = new #only take the ones you can continue with 

    print("ending")
    print(ret)
    # Construct the final list of substrings.
    return [''.join(el[0] for el in a) for a in ret if len(a) > 0]

delims = input().strip().split()
s = input().strip()

print(multiSplit(s, delims))

# Example usage
# s = "yourstring"
# delim = ["delim1", "delim2"]
# result = multiSplit(s, delim)


# def multiSplit(delims, s):
#     res = [[]]
#     #build trie
#     trie = {}
#     for word in delims:
#         ptr = trie 
#         for c in word:
#             if c not in ptr:
#                 ptr[c] = {}
#             ptr = ptr[c]
#         ptr[None] = len(word)
    
    
#     ptrs = []


#     for i, char in enumerate(s):
#         res[-1].append((i, char))
#         ptrs.append(trie)
#         toProcess = []

#         for ptr in ptrs:
#             if char not in ptr:
#                 continue
            
#             ptr = ptr[char]
#             toProcess.append(ptr)

#             if None in ptr:
#                 howFar = i - ptr[None]

#                 while len(res) > 0 and (len(res[-1]) == 0 or res[-1][-1][0] > howFar):
#                     if len(res[-1]) == 0:
#                         res.pop()
#                     else:
#                         res[-1].pop()
#                 res.append([])
        
#         ptrs = toProcess
    
#     return [''.join(x[1] for x in elem) for elem in res]
                


# delims = input().strip().split()
# s = input().strip()

# print(multiSplit(delims, s))
            