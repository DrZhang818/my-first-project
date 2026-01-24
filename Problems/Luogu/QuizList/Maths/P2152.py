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

sys.set_int_max_str_digits(100000)

a = II();
b = II();
print(math.gcd(a, b))