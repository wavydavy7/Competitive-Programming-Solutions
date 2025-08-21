import random

def sim():
    cnt16 = 0
    cnt25 = 0
    cnt34 = 0
    for i in range(20):
        r = random.randint(1, 6)
        if r == 1 or r == 6:
            cnt16 += 1
        elif r == 2 or r == 5:
            cnt25 += 1
        else:
            cnt34 += 1
    
    return cnt16 * cnt25 * cnt34

def main():
    tot = 0
    for i in range(1000):
        tot += (sim() - 254)*(sim() - 254)
    print(tot / 1000.0)

main()