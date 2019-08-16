T = int(input())
for i in range(0, T):
    n = int(input())
    odd = 0
    even = 0
    other = 0
    for j in range(0, n):
        x, y = map(int, input().split())
        if x % 2 != y % 2:
            other += 1
        elif x % 2 == 1 and y % 2 == 1:
            odd += 1
        else:
            even += 1
    if other > 0:
        print(2 ** (n - 1))
    elif odd % 2 == 0:
        print(0)
    else:
        print(2 ** n)
