#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
void solve1(vector<int> &a) {
    ll sum = 0;
    int n = a.size() - 1;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
    }
    if(n % 2 == 0) {
        if(sum % 2 == 1) {
            cout << "First\n";
        } else {
            cout << "Second\n";
        }
    } else {
        bool tag = 1;
        while(1) {
            if(sum % 2 == 0) {
                if(tag) {
                    cout << "First\n";
                } else {
                    cout << "Second\n";
                }
                return;
            } else {
                int c = 0, has1 = false;
                for(int i = 1; i <= n; i++) {
                    if(a[i] & 1) {
                        c++;
                        if(a[i] == 1) {
                            has1 = true;
                        }
                    }
                }
                if(has1) {
                    if(sum % 2 == 0) {
                        if(tag) {
                            cout << "First\n";
                        } else {
                            cout << "Second\n";
                        }
                    } else {
                        if(tag) {
                            cout << "Second\n";
                        } else {
                            cout << "First\n";
                        }
                    }
                    return;
                }
                if(c >= 2) {
                    if(tag) {
                        cout << "Second\n";
                    } else {
                        cout << "First\n";
                    }
                    return;
                } else {
                    int g = 0;
                    sum = 0;
                    for(int i = 1; i <= n; i++) {
                        if(a[i] % 2 == 0) {
                            g = gcd(g, a[i]);
                        } else {
                            a[i] -= 1;
                            g = gcd(g, a[i]);
                        }
                    }
                    for(int i = 1; i <= n; i++) {
                        a[i] /= g;
                        sum += a[i];
                    }
                }
            }
            tag ^= 1;
        }
    }
}

void solve() {
    int n = 3;
    auto dfs = [&](this auto &&self, vector<int> a) -> bool {
        int c = count(a.begin() + 1, a.end(), 1);
        if(c == n) {
            return false;
        }
        for(int i = 1; i <= n; i++) {
            if(a[i] == 1) continue;
            auto na = a;
            na[i] -= 1;
            int g = 0;
            for(int j = 1; j <= n; j++) {
                g = gcd(g, na[j]);
            }
            for(int j = 1; j <= n; j++) {
                na[j] /= g;
            }
            if(!self(na)) {
                return true;
            }
        }
        return false;
    };
    vector<int> a(4);

    for(int i = 3; i <= 20; i++) {
        for(int j = i; j <= 20; j++) {
            for(int k = j; k <= 20; k++) {
                if(gcd(gcd(i, j), k) != 1) continue;
                a[1] = i;
                a[2] = j;
                a[3] = k;
                solve1(a);
                if(dfs(a)) {
                    cerr << "First\n";
                } else {
                    cerr << "Second\n";
                }
            }
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
