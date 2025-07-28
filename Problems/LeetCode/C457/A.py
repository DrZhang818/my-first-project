mp = {
    "electronics": 0,
    "grocery": 1,
    "pharmacy": 2,
    "restaurant": 3,
}

class info:
    def __init__(self, s: str, id: int):
        self.s = s
        self.id = id
    def __lt__(self, other):
        if self.id != other.id:
            return self.id < other.id
        return self.s < other.s
class Solution:
    def validateCoupons(self, a: List[str], b: List[str], tag: List[bool]) -> List[str]:
        n = len(a)
        res = []
        for s, t, flag in zip(a, b, tag):
            id = mp.get(t, -1)
            if s and id >= 0 and flag and all(c == '_' or c.isalnum() for c in s):
                res.append(info(s, u))
        res.sort()
        ans = [o.s for o in res]
        return ans
