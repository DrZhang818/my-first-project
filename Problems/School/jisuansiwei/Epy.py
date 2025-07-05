import sys, re
from collections import Counter

def solve():
    [print(w, c) for w, c in sorted(Counter(re.findall('[a-z]+', sys.stdin.read().lower())).items())]

if __name__ == '__main__':
    solve()