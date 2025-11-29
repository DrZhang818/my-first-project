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

    # if packages:
    #     from io import BytesIO, IOBase

    #     import random
    #     import os

    #     import bisect
    #     import typing
    #     from collections import Counter, defaultdict, deque
    #     from copy import deepcopy
    #     from functools import cmp_to_key, lru_cache, reduce
    #     from heapq import merge, heapify, heappop, heappush, heappushpop, nlargest, nsmallest
    #     from itertools import accumulate, combinations, permutations, count, product
    #     from operator import add, iand, ior, itemgetter, mul, xor
    #     from string import ascii_lowercase, ascii_uppercase, ascii_letters
    #     from sortedcontainers import SortedList
    #     from typing import *
    #     BUFSIZE = 4096

def min(a, b): return a if a < b else b

def max(a, b): return a if a > b else b


T = II()
for _ in range(T):
    A, B, C, X, Y, L = LII()
    ans = inf
    if L <= X:
        ans = A
    elif L <= X + Y:
        ans = min(ans, A + B * (L - X))
        ans = min(ans, A * (L // X) + B * (L % X))
        ans = min(ans, A * ((L + X - 1) // X))
    else:
        ans = min(ans, A * ((L + X - 1) // X))
        ans = min(ans, A * (L // X) + B * min(L % X, Y * (L // X)) + C * max(0, L % X - Y * (L // X)))
        ans = min(ans, A * (L // X) + B * min(L % X, Y) + C * max(0, L % X - Y))
        ans = min(ans, A + B * Y + C * (L - X - Y))
        R = X + Y
        t = L // R
        ans = min(ans, A * t + B * max(0, min(L - X * t, Y * t)) + C * max(0, (L - X * t - max(0, min(L - X * t, Y * t)))))
        t += 1
        ans = min(ans, A * t + B * max(0, min(L - X * t, Y * t)) + C * max(0, (L - X * t - max(0, min(L - X * t, Y * t)))))
    print(ans)
