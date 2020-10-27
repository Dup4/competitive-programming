
f = {}
_f = ['0' for i in range(0, 36)]

def init():
    t = 0
    for i in range(ord('A'), ord('Z') + 1):
        f[i] = t
        t += 1
    for i in range(ord('a'), ord('z') + 1):
        f[i] = t
        t += 1
    for i in range(ord('0'), ord('9') + 1):
        f[i] = t
        t += 1
    f[ord('+')] = t
    t += 1
    f[ord('/')] = t
    t += 1
    t = 0
    for i in range(ord('0'), ord('9') + 1):
        _f[t] = chr(i)
        t += 1
    for i in range(ord('A'), ord('Z') + 1):
        _f[t] = chr(i)
        t += 1

init()

def num2bit(ch):
    s = ""
    for i in range(5, -1, -1):
        s += chr(((ch >> i) & 1) + ord('0'))
    return s

def main():
    s = input()
    _s = ""
    _cnt = 0
    for item in s:
        if item == '=':
            _cnt += 1
        else:
            _s += num2bit(f[ord(item)])
    cnt = 0
    for item in _s:
        if item == '1':
            cnt = 0
        else:
            cnt = cnt + 1
    # print(_s)
    # print(_cnt, cnt)
    _s = _s.rstrip('0')
    for i in range(0, cnt - _cnt * 2):
        _s = _s + '0'
    if len(_s) == 0:
        print('0')
        return
    num = 0
    for item in _s:
        num = (num << 1) + (ord(item) - ord('0'))
    ans = ""
    while num > 0:
        ans += _f[num % 36]
        num //= 36
    print(ans[::-1])

main()