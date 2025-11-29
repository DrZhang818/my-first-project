#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = int(1E3);
void solve() {
    vector<ll> W(N + 1);
    for(int i = 1; i <= N; i++) {
        W[i] = 1LL * i * i * i;
    }
    int sum = 0;
    for(int n = 1; n <= 1000000; n++) {
        int c = 0;
        for(int a = 1, b = 1; a <= N; a++) {
            while(a > b && W[a] - W[b] > n) ++b;
            if(W[a] - W[b] == n) {
                c++;
                if(c >= 3) {
                    if(c == 3) {
                        cerr << n << " :\n";
                    }
                    cerr << a << " " << b << "\n";
                }
                ++sum;
            }
        }
        if(c >= 3) {
            cerr << "\n";
        }
    }
    cerr << sum;
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
