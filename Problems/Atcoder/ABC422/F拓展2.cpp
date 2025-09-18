#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y, v;
};
void solve() {
    int N, x0;
    cin >> N >> x0;
    vector<info> a(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> a[i].x;
    }
    for(int i = 1; i <= N; i++) {
        cin >> a[i].y;
    }
    for(int i = 1; i <= N; i++) {
        cin >> a[i].v;
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
