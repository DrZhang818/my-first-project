import collections
from sortedcontainers import SortedList

class DSU:
    def __init__(self, n):
        self.fa = list(range(n))
    def find(self, o):
        if self.fa[o] == o:
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

        st = collections.defaultdict(SortedList)
        for i in range(1, n + 1):
            f = g.find(i)
            st[f].add(i)

        ans = []
        for op, x in Q:
            f = g.find(x)
            if op == 1:
                if len(st[f]) > 0:
                    if x in st[f]:
                        ans.append(x)
                    else:
                        ans.append(st[f][0])
                else:
                    ans.append(-1)
            elif len(st[f]) > 0 and x in st[f]:
                    st[f].remove(x)
        return ans

