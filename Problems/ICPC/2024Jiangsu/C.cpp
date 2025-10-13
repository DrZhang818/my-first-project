#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n;
int mod(int x) {
    return (x % n + n) % n;
}
int query(int x) {
    x = mod(x);
    x++;
    cout << "? " << x << endl;
    int res;
    cin >> res;
    return res;
}
void answer(int x, int y) {
    x++;
    y++;
    cout << "! " << x << " " << y << endl;
}
void solve() {
    cin >> n;
    int a = query(0), b = query(n >> 1), tx;
    int x, y;
    if(a <= b) {
        x = 0;
        tx = a;
    } else {
        x = n >> 1;
        tx = b;
    }
    a = query(x + 1);
    b = query(x - 1);
    if(a == b) {
        int l = -1, r = n / 2 + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(query(x + mid) == tx) {
                l = mid;
            } else {
                r = mid;
            }
        }
        x = mod(x + l);
        y = mod(x - tx);
    } else if(a < b) {
        int l = -1, r = n / 2 + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(query(x + mid) == tx - 2 * mid) {
                l = mid;
            } else {
                r = mid;
            }
        }
        x = mod(x + l);
        y = mod(x + (tx - 2 * l));
    } else {
        int l = -1, r = n / 2 + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(query(x - mid) == tx - 2 * mid) {
                l = mid;
            } else {
                r = mid;
            }
        }
        x = mod(x - l);
        y = mod(x - (tx - 2 * l));
    }
    answer(x, y);
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
