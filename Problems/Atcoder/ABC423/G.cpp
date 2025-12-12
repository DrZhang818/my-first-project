#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> B(8);

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll mod(ll a, ll p) {
    return (a % p + p) % p;
}
// 求解 ax = c (mod b) 的最小非负整数解
ll mod_inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

void solve() {
    int K;
    string S;
    cin >> K >> S;
    int lenK = to_string(K).size();
    int n = S.size();
    vector<int> power(n + 15);
    power[0] = 1;
    for(int i = 1; i <= n + 14; i++) {
        power[i] = 1LL * power[i - 1] * 10 % K;
    }

    int num = 0;
    for(char c : S) {
        num = (1LL * num * 10 + c - '0') % K; 
    }

    if(num == 0) {
        cout << S << "\n";
        return;
    }

    string ans;
    for(int lenR = 0; lenR <= lenK; lenR++) {
        int l = -1, r = -1;
        if(lenR <= lenK - lenR) {
            for(int R = 0; R < B[lenR]; R++) {
                int a = power[n + lenR];
                int b = (K - (1LL * num * power[lenR] + R) % K) % K;
                int c = K;
                int g = gcd(a, c);
                if(b % g != 0) {
                    continue;
                }
                a /= g;
                b /= g;
                c /= g;
                int x = mod_inv(a, c);
                int L = 1LL * x * b % c;

                if(l == -1 || L < l) {
                    l = L;
                    r = R % K;
                }
            }
        } else {
            for(int L = 0; L < B[lenK - lenR]; L++) {
                int R = (K - (1LL * L * power[n + lenR] % K + 1LL * num * power[lenR] % K) % K) % K;
                int len = to_string(R).size();
                if(len <= lenR) {
                    l = L % K;
                    r = R;
                    break;
                }
            }
        }
        if(l == -1 && r == -1) {
            continue;
        }
        string cur;
        if(l != 0) cur += to_string(l);
        cur += S;
        if(lenR != 0) {
            string tmp = to_string(r);
            for(int i = 0; i < lenR - int(tmp.size()); i++) cur += '0';
            cur += tmp;
        }
        if(ans == "" || cur.size() < ans.size() || cur.size() == ans.size() && cur < ans) {
            ans = cur;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    B[0] = 1;
    for(int i = 1; i <= 7; i++) {
        B[i] = B[i - 1] * 10;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
