def check(s):
    return s==s[::-1]

def main():
    n=int(input())
    for _ in range(n):
        s=input()
 		if check(s):
            print("Yes")
            continue
        legal=False
        for i in range(len(s)):
			# print(s[:i] + s[i + 1:])
            if check(s[:i]+s[i + 1:]):
                legal=True
                break
        if legal:
            print("Yes")
        else:
            print("No")

main()

