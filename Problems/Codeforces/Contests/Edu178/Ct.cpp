#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


string s;
int c1 = 0, c2 = 0;
void solve() {
    int n = 50;
    if(s[n] == 'B') {
        int cnt = 0;
        for(int i = 1; i <= n; i++) cnt += s[i] == 'B';
        if(cnt > 1) {
            c2++;
        } else {
            c1++;
        }
    } else {
        if(s[1] == 'A' || s[n - 1] == 'A') {
            c1++;
        } else {
            c2++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    srand(time(0));
    for(int i = 0; i < 10000000; i++) {
        s = "#";
        for(int j = 0; j < 50; j++) {
            int t = rand() % 2;
            s += t == 0 ? "A" : "B";
        }
        solve();
        if(i % 100000 == 0) {
            cerr << i / 100000 << "\n";
        }
    }
    cout << fixed << setprecision(2) << (db)c1 / (c1 + c2) << "\n";
    return 0;
}
