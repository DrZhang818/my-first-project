import io, os, sys
input = lambda: sys.stdin.readline().strip()

import math
inf = math.inf

def I():
    return input()

def II():
    return int(input())

def MII():
    return map(int, input().split())

def LI():
    return input().split()

def LII():
    return list(map(int, input().split()))

def LFI():
    return list(map(float, input().split()))

def GMI():
    return map(lambda x: int(x) - 1, input().split())

def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))

n, k = LII()
L = 1

for i in range(1, k + 1):
    mod = 10 ** i
    p = n % mod
    ok = False
    for j in range(1, 11):
        if p == pow(n, L * j + 1, mod):
            L *= j
            ok = True
            break
    if not ok:
        L = -1
        break
print(L)        
