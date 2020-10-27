

f = [0 for i in range(0, 10001)]
f[0] = 0
f[1] = 1
f[2] = 1

for i in range(3, 10000):
    f[i] = f[i - 1] + f[i - 2]

def main():
    while True:
        try:
            n = int(input())
            print(f[n])
        except:
            return

main()