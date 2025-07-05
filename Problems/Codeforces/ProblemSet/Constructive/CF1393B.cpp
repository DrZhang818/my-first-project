#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1393/B

constexpr int MX = 100005;
void solve() { 
    int n;
    cin >> n;
    vector<int> cnt(MX);
    for(int i = 1; i <= n; i++) {
        int x; 
        cin >> x;
        cnt[x] += 1;
    }
    int c2 = 0, c4 = 0;
    for(int i = 1; i < MX; i++) {
        c2 += cnt[i] / 2;
        c4 += cnt[i] / 4;
    }
    int q;
    cin >> q;
    while(q--) {
        char c;
        int x;
        cin >> c >> x;
        int pre = cnt[x];
        cnt[x] += c == '+' ? 1 : -1;
        c2 += (cnt[x] / 2) - (pre / 2);
        c4 += (cnt[x] / 4) - (pre / 4);
        if(c4 >= 1 && c2 >= 4) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
