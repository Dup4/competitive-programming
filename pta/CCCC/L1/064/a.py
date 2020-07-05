

def gao():
    str = input()
    print(str)
    str = str.strip()
    
    print("AI: " + str)



def main():
    n = int(input())
    for i in range(n):
        gao()

main()