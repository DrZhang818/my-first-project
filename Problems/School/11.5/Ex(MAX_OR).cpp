#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}

int BF(vector<int> &a, int k) {
    int ans = 0;
    int n = a.size();
    for(int s = 0; s < 1 << n; s++) {
        if(__builtin_popcount(s) != k) {
            continue;
        }
        int cur = 0;
        for(int i = 0; i < n; i++) {
            if(s >> i & 1) {
                cur |= a[i];
            }
        }
        ans = max(ans, cur);
    }
    return ans;
}

int Greedy(vector<int> &a, int k) {
    int ans = 0;
    int n = a.size();
    vector<int> val(30);
    for(int i = 0; i < n; i++) {
        for(int s = 0; s < 30; s++) {
            if(a[i] >> s & 1) {
                val[s] = max(val[s], a[i]);
            }
        }
    }
    for(int i = 29; i >= 0; i--) {
        if(ans >> i & 1) {
            continue;
        }
        if(val[i] == 0) {
            continue;
        }
        if(k > 0) {
            ans |= val[i];
            k--;
        }
    }
    return ans;
}

void solve() {
    int n = 3, k = 2, V = 10;
    vector<int> a(n);
    int T = 100000;
    for(int _ = 1; _ <= T; _++) {
        for(int i = 0; i < n; i++) {
            a[i] = get(0, V);
        }
        int ans1 = BF(a, k);
        int ans2 = Greedy(a, k);
        if(ans1 != ans2) {
            cerr << "WA!\n";
            for(int i = 0; i < n; i++) {
                cerr << a[i] << " \n"[i == n - 1];
            }
            cerr << ans1 << " " << ans2 << "\n";
            cerr << "\n";
        } 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
