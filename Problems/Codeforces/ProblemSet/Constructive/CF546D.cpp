#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
constexpr int inf = 1000000000;

//https://codeforces.com/problemset/problem/546/D
vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(p == minp[i]) break;
        }
    }
}
int pre[5000001];
void solve() {
    int a, b;
    cin >> a >> b;
    cout << pre[a] - pre[b] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(5000000);
    for(int i = 2; i <= 5000000; i++) {
        int cnt = 0, x = i;
        while(x > 1) {
            cnt++;
            x /= minp[x];
        }
        pre[i] = pre[i - 1] + cnt;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
