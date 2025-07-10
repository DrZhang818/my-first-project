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
        from typing import *
        BUFSIZE = 4096

t = II()
outs = []

for _ in range(t):
    n = II()
    a = LII()
    a.sort(key = abs)
    ok = all(a[i] * a[i] == a[i - 1] * a[i + 1] for i in range(1, n - 1))
    cnt = Counter(1 if x > 0 else -1 for x in a)
    pos = cnt[1]
    neg = cnt[-1]
    if abs(a[0]) == abs(a[-1]) and abs(pos - neg) <= 1: 
        ok = True
    if ok:
        outs.append("Yes")
    else:
        outs.append("No")
print('\n'.join(outs))

