#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int query(string s) {
    cout << 1 << " " << s << endl;
    int res;
    cin >> res;
    assert(res != -1);
    return res;
}

void answer(int i, int x) {
    cout << 0 << " " << i << " " << x << endl;
    int res;
    cin >> res;
    assert(res != -1);
}

void solve() {
    int n;
    cin >> n;
    int tot = query("1");
    int sum = query("01") + query("11");
    if(tot == sum) {
        answer(1, 0);
    } else {
        answer(1, 1);
    }
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
