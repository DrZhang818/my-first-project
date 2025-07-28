from collections import defaultdict

class DSU:
    def __init__(self, n):
        self.fa = [x for x in range(n)]
    def find(self, o):
        if o == self.fa[o]:
            return o
        self.fa[o] = self.find(self.fa[o])
        return self.fa[o]
    def merge(self, u, v):
        u = self.find(u)
        v = self.find(v)
        if u != v:
            self.fa[u] = v

class Solution:
    def processQueries(self, n: int, e: List[List[int]], Q: List[List[int]]) -> List[int]:
        g = DSU(n + 1)
        for u, v in e:
            g.merge(u, v)
        heap = defaultdict(list)
        for i in range(1, n + 1):
            f = g.find(i)
            heap[f].append(i)
        for a in heap.values():
            heapify(a)
        vis = [False] * (n + 1)
        ans = []
        for op, x in Q:
            if op == 2:
                vis[x] = True
                continue
            if not vis[x]:
                ans.append(x)
                continue
            h = heap[g.find(x)]
            while h and vis[h[0]]:
                heappop(h)
            ans.append(h[0] if h else -1)
        return ans        