def solve(coins, n):
    # Add a placeholder for index 0 to match the 1-based indexing
    coins = [0] + coins
    scores = [[(0, 0) for _ in range(n+1)] for _ in range(n+1)] #no need for bitmasking, range is better

    # Calculating the base scores for i=j
    for i in range(1, n+1):
        scores[i][i] = (coins[i], 0)  #one element is itself ofc

    # l holds the total length of the range i..j
    for l in range(1, n):
        for i in range(1, n-l+1):
            j = i + l #starting at i and including some length
            # If picking coin at i is better than at j
            if coins[i] + scores[i+1][j][1] >= coins[j] + scores[i][j-1][1]:  #if picking i, left, is better than j, right 
                scores[i][j] = (coins[i] + scores[i+1][j][1], scores[i+1][j][0]) #the first player is now the second player after their turn 
            else:
                scores[i][j] = (coins[j] + scores[i][j-1][1], scores[i][j-1][0])

    # Our answer is the best score for the original range, i.e., 1..n
    return scores[1][n][0] #first person 



def main():
    N = int(input())
    arr = list(map(int, input().split()))
    result = solve(arr, N)
    print(result)

main()
