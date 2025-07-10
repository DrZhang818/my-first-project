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

n, m, k = LII()
a = [[inf for _ in range(m)] for _ in range(n)]
q = deque()
dir = [(0, 1), (0, -1), (1, 0), (-1, 0)]
for _ in range(k):
    x, y = LGMI()
    a[x][y] = 0
    q.append([x, y])
while q:
    x, y = q.popleft()
    for dx, dy in dir:
        nx = x + dx
        ny = y + dy
        if nx < 0 or nx >= n or ny < 0 or ny >= m or a[nx][ny] < inf: continue
        cnt = 0
        for u, v in dir:
            mx = nx + u
            my = ny + v
            if mx < 0 or mx >= n or my < 0 or my >= m or a[mx][my] > a[x][y]: continue
            cnt += 1
        if cnt >= 2:
            a[nx][ny] = a[x][y] + 1
            q.append([nx, ny])
ans = 0
for i in range(n):
    for j in range(m):
        if a[i][j] < inf:
            ans += a[i][j]
print(ans)