#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    ll sum = 0;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        a[i] = x;
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
                    sum -= n;
                    if(sum % 2 == 1) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
