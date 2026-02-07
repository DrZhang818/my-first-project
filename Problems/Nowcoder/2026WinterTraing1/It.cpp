#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int solve(int l, int r) {  

    int tl = l, tr = r;

    if(__lg(l) == __lg(r)) {
        if(l == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    int ans = 0;

    int low = 0;
    for(int i = 29; i >= 0; i--) {
        if(~r >> i & 1) continue;
        if(l >> i & 1) {
            low += 1 << i;
            if(low > ans) {
                break;
            }
            l ^= 1 << i;
            r ^= 1 << i;
            continue;
        }

        int high = __lg(r);
        int nr = (1 << high) - 1;

        ans = max(ans, low + (r ^ (1 << high)) + 1);

        r = nr;
    }


    if(tl <= ans && ans <= tr) {
        ans = tr + 1;
    }

    return ans;
}

int brute(int l, int r) {
    int len = r - l + 1;
    vector<int> a(len);
    iota(a.begin(), a.end(), l);
    set<int> st;
    for(int i = 0; i <= r + 1; i++) {
        st.insert(i);
    }
    for(int s = 0; s < 1 << len; s++) {
        int sand = numeric_limits<int>::max();
        for(int i = 0; i < len; i++) {
            if(s >> i & 1) {
                sand &= a[i];
            }
        }
        st.erase(sand);
    }
    return *st.begin();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int len = 14;
    for(int l = 0; l <= 150; l++) {
        int ans1 = solve(l, l + len);
        int ans2 = brute(l, l + len);
        if(ans1 != ans2) {
            cerr << "WA! \n";
            cerr << l << " " << l + len << " brute: " << ans2 << " solve: " << ans1 << "\n"; 
        }
    }

    for(int s = 3; s <= 8; s++) {
        cerr << bitset<5>(s) << "\n";
    }

    return 0;
}
