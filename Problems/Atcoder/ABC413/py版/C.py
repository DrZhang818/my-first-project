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

q = II()
a = []
l = 0
outs = []
for _ in range(q):
    Q = LII()
    op = Q[0]
    if op == 1:
        c, x = Q[1:]
        a.append([c, x])
    else:
        k = Q[1]
        res = 0
        while k:
            c, x = a[l]
            mn = min(c, k)
            k -= mn
            a[l][0] -= mn
            res += x * mn
            if a[l][0] == 0: l += 1
        outs.append(res)
print(*outs, sep = '\n')
