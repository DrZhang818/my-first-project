#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
using T = pair<array<int,4>, array<int,6>>;

int Hash(T &a) {
    int H = 0;
    for(int x : a.first) {
        H = H << 3 | x;
    }
    for(int x : a.second) {
        H = H << 3 | x;
    }
    return H;
}

void solve() {
    int n;
    cin >> n;
    array<int,4> cnt {};
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        if(s[1] == 'D') cnt[0]++;
        else if(s[1] == 'C') cnt[1]++;
        else if(s[1] == 'H') cnt[2]++;
        else cnt[3]++;
    }
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        ans += cnt[i] / 5;
        cnt[i] %= 5;
    }
    array<int,6> has {};
    for(int i = 0; i < 6; i++) {
        cin >> has[i];
    }

    unordered_set<int> st;

    auto dfs = [&](auto &&self, T &cur) -> int {
        int H = Hash(cur);
        st.insert(H);
        auto &a = cur.first;
        auto &b = cur.second;
        int res = 0;
        for(int i = 0; i < 4; i++) {
            if(b[i]) {
                vector<int> vec;
                for(int j = 0; j < 4; j++) {
                    if(j != i) {
                        vec.push_back(j);
                    }
                }
                for(int x = 0; x <= a[vec[0]] && x <= 3; x++) {
                    for(int y = 0; y <= a[vec[1]] && x + y <= 3; y++) {
                        for(int z = 0; z <= a[vec[2]] && x + y + z <= 3; z++) {
                            auto na = a;
                            auto nb = b;
                            na[vec[0]] -= x;
                            na[vec[1]] -= y;
                            na[vec[2]] -= z;
                            na[i] += x + y + z;
                            nb[i] = 0;
                            int val = na[i] / 5;
                            na[i] %= 5;
                            T nxt = {na, nb};
                            int nH = Hash(nxt);
                            if(st.contains(nH)) {
                                continue;
                            }
                            res = max(res, self(self, nxt) + val);
                        }
                    }
                }
            }
        }
        if(b[4]) {
            for(int i = 0; i < 4; i++) {
                if(a[i]) {
                    for(int j = 0; j < 4; j++) {
                        if(j == i) {
                            continue;
                        }
                        auto na = a;
                        auto nb = b;
                        nb[4] = 0;
                        na[i]--;
                        na[j]++;
                        int val = na[j] / 5;
                        na[j] %= 5;
                        T nxt = {na, nb};
                        int nH = Hash(nxt);
                        if(st.contains(nH)) {
                            continue;
                        }
                        res = max(res, self(self, nxt) + val);
                    }
                }
            }
        }
        if(b[5]) {
            for(int i = 0; i < 4; i++) {
                if(a[i]) {
                    for(int j = 0; j < 4; j++) {
                        if(j == i || a[j] == 0) {
                            continue;
                        }
                        auto na = a;
                        auto nb = b;
                        nb[5] = 0;
                        na[i]--;
                        na[j]++;
                        int val = na[j] / 5;
                        na[j] %= 5;
                        T nxt = {na, nb};
                        int nH = Hash(nxt);
                        if(st.contains(nH)) {
                            continue;
                        }
                        res = max(res, self(self, nxt) + val);
                    }
                }
            }
        }
        return res;
    };  

    T cur = {cnt, has};
    ans += dfs(dfs, cur);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
