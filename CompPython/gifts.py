def get_highest_bit(mask):
    """
    Gets the highest bit in a binary mask.
    """
    for i in range(N - 1, -1, -1):
        if mask & (1 << i):
            return i
    return 0

# Read the value of N
N = int(input())

# Read the wishlist preferences
wishlist = []
for _ in range(N):
    row = list(map(int, input().split()))
    wishlist.append([x - 1 for x in row])

# Initialize the dynamic programming array
dp = [[0] * N for _ in range(1 << N)]

# Base case: if there are no locations to visit, there is 1 way to create a cycle (having none)
for i in range(N):
    dp[0][i] = 1

# Loop through all possible bitmasks
for mask in range(1, 1 << N):

    # Find the highest set bit in the bitmask, which represents the goal node
    end = get_highest_bit(mask)

    # Iterate from 0 to the goal node
    for i in range(end + 1):
        for j in range(N):
            want = wishlist[i][j]

            # If we can go to the vertex, update the number of ways
            if mask & (1 << want):
                dp[mask][i] += dp[mask ^ (1 << want)][want]

            # If want == i, there are no more edges past this point
            if want == i:
                break


    # Copy the number of ways with the end node to all other indices
    for i in range(end + 1, N):
        dp[mask][i] = dp[mask][end]

# Read the number of queries
Q = int(input())

res = []
# Process each query
for _ in range(Q):
    breed = input().strip() #creates a list of the characters

    # Calculate the binary masks for 'H' and 'G'
    h = 0
    g = 0
    for j in range(N):
        if breed[j] == 'H':
            h += 1 << j
        elif breed[j] == 'G':
            g += 1 << j

    # Compute the number of ways cycles can be created for the given breeds
    result = dp[h][N - 1] * dp[g][N - 1]
    res.append(result)

for i in range(Q):
    print(res[i])
