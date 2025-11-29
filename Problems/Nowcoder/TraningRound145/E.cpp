#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

bool ck(ll a1, ll d1, ll a2, ll d2, ll n) {
    ll ans1 = 1, ans2 = 1;
    unordered_set<ll> st;
    for(int i = 1; i <= n; i++) {
        ans1 = (ans1 * a1) % MOD;
        st.insert(a1);
        a1 += d1;
    }
    ans1 = (ans1 + MOD) % MOD;
    for(int i = 1; i <= n; i++) {
        ans2 = (ans2 * a2) % MOD;
        st.insert(a2);
        a2 += d2;
    }
    ans2 = (ans2 + MOD) % MOD;
    return ans1 == ans2 && st.size() == n * 2;
}

void solve() {
    // int n = 11;
    int L = -100, R = 100, mx = 100;
    for(int n = 3; n <= 50; n += 2) {
        cerr << "n: " << n << "\n";
        for(int a1 = L; a1 <= R; a1++) {
            for(int d1 = 1; d1 <= 1; d1++) {
                for(int a2 = L; a2 <= R; a2++) {
                    for(int d2 = 1; d2 <= mx; d2++) {
                        if(ck(a1, d1, a2, d2, n)) {
                            for(int i = 1, t = a1; i <= n; i++) {
                                cerr << t << " \n"[i == n];
                                t += d1;
                            }
                            for(int i = 1, t = a2; i <= n; i++) {
                                cerr << t << " \n"[i == n];
                                t += d2;
                            }
                            // cerr << "\n";
                            goto end;
                        } 
                    }
                }
            }
        }
        end:
        cerr << "\n";
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
