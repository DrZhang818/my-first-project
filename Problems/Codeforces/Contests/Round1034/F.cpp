#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> minp, primes;
void sieve(int n) { 
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[p] == i) break;
        }
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    set<int> st;
    for(int i = 2; i <= n; i++) {
        if(minp[i] == i) continue;
        int x = i;
        while(x != 1) {
            if(st.count(minp[x])) {
                x /= minp[x];
            } else {
                break;
            }
        }
        if(x == 1) x = i;
        swap(p[i], p[minp[x]]);
        st.insert(minp[x]);
    }
    for(int i = 1; i <= n; i++) {
        cout << p[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(100005);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

