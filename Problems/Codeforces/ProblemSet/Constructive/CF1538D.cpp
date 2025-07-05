#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1538/D
int get(int x) {
    int cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        while(x % i == 0) {
            cnt++;
            x /= i;
        }
    }
    if(x != 1) cnt++;
    return cnt;
}
void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    int g = __gcd(a, b);
    int mn = 0, mx = 0;
    if(a != g) mn++;
    if(b != g) mn++;
    if(a == b) mn = 2;
    mx = get(a) + get(b);
    if(mn <= k && k <= mx) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
