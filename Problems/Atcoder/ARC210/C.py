stand_input, packages = 1, 1
if 1:
    if stand_input:
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

    if packages:
        from io import BytesIO, IOBase

        import random
        import os

        import bisect
        import typing
        from collections import Counter, defaultdict, deque
        from copy import deepcopy
        from functools import cmp_to_key, lru_cache, reduce
        from heapq import merge, heapify, heappop, heappush, heappushpop, nlargest, nsmallest
        from itertools import accumulate, combinations, permutations, count, product
        from operator import add, iand, ior, itemgetter, mul, xor
        from string import ascii_lowercase, ascii_uppercase, ascii_letters
        from sortedcontainers import SortedList
        from typing import *
        BUFSIZE = 4096


T = II()
outs = []

for _ in range(T):
    n, m = LII()
    a = LII()
    na = a[:]
    for i in range(len(na)):
        x = na[i]
        na[i] %= 10
        if x >= 10:
            if i + 1 >= len(na):
                na.append(0)
            na[i + 1] += x // 10
    a += [0] * (len(na) - len(a))

    pow10 = 10 ** (len(na) - 1)
    ans = 0
    x = 0
    for i in range(len(na) - 1, -1, -1):
        cans = na[i] // m
        ans += cans * pow10
        x += cans * m * pow10
        cur = a[i] * pow10
        rem = na[i] % m
        if cur <= x:
            x -= cur
        else:
            rem -= (cur - x) // pow10
            x = 0
        if i > 0:
            na[i - 1] += rem * 10
        pow10 //= 10
    outs.append(ans)
print('\n'.join(map(str, outs)))

