#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2114/problem/A
void solve() {
    int n;
    cin >> n;
    if(sqrt(n) != (int)sqrt(n)) {
        cout << -1 << "\n";
        return;
    }
    int t = (int)sqrt(n);
    cout << t / 2 << " " << t - t / 2 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
