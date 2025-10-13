#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    string sn;
    cin >> sn;
    int m;
    cin >> m;
    int len = sn.size();
    vector<int> n(len);
    for(int i = 0; i < len; i++) {
        n[i] = sn[len - 1 - i] - '0';
    }
    int res = 0;
    for(int i = len - 1; i >= 0; i--) {
        res = (10LL * res + n[i]) % m;
    }
    res = m - res;
    for(int i = 0; i < len || res > 0; i++) {
        if(i >= len) {
            len++;
            n.push_back(0);
        }
        if(res > 0) {
            n[i] += res % 10;
            res /= 10;
        }
        int carry = n[i] / 10;
        n[i] %= 10;
        res += carry;
    }    
    string ans;
    for(int i = len - 1; i >= 0; i--) {
        ans += n[i] + '0';
    }
    string sm = to_string(m);
    int lenm = sm.size();
    if(sn.size() > sm.size()) {
        len = sn.size();
        n.resize(len);
        for(int i = 0; i < len; i++) {
            n[i] = sn[len - 1 - i] - '0';
        }
        n[0]++;
        for(int i = 0; i < len; i++) {
            if(n[i] >= 10) {
                n[i] -= 10;
                if(i == len - 1) {
                    len++;
                    n.push_back(0);
                }
                n[i + 1]++;
            }
        }
        auto work = [&]() {
            bool ok = false;
            for(int i = len - 1; i >= lenm - 1; i--) {
                ll res = 0;
                for(int j = 0; j < lenm; j++) {
                    res = 10 * res + n[i - j];
                }
                if(res == m) {
                    ok = true;
                    break;
                }
            }
            if(ok) {
                string t;
                for(int i = len - 1; i >= 0; i--) {
                    t += n[i] + '0';
                }
                if(t.size() < ans.size() || t.size() == ans.size() && t < ans) {
                    ans = t;
                }
            } else {
                auto tn = n;
                for(int i = len - 1; i >= lenm - 1; i--) {
                    ll cur = 0;
                    bool ok = true;
                    for(int j = 0; j < lenm; j++) {
                        cur = 10 * cur + n[i - j];
                        if(n[i - j] != sm[j] - '0') {
                            if(i - j >= lenm) {
                                ok = false;
                            }
                        }
                    }
                    if(!ok || cur > m) {
                        continue;
                    }
                    string t;
                    for(int j = 0; j < lenm; j++) {
                        n[i - j] = sm[j] - '0';
                    }
                    for(int j = i - lenm; j >= 0; j--) {
                        n[j] = 0;
                    }
                    for(int j = len - 1; j >= 0; j--) {
                        t += n[j] + '0';
                    }
                    if(t.size() < ans.size() || t.size() == ans.size() && t < ans) {
                        ans = t;
                    }
                    n = tn;
                }
            }
        };
        work();
        for(int i = 0; i < lenm; i++) {
            n[i] = 0;
        }
        n[lenm]++;
        for(int i = 0; i < len; i++) {
            if(n[i] >= 10) {
                n[i] -= 10;
                if(i == len - 1) {
                    len++;
                    n.push_back(0);
                }
                n[i + 1]++;
            }
        }
        work();
    }
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
