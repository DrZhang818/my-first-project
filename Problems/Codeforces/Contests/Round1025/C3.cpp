#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2109/problem/C3
void solve() {
    int n, x;
    cin >> n;
    cout << "mul 999999999" << endl;
    cin >> x;
    cout << "digit" << endl;
    cin >> x;
    if(n != 81) {
        cout << "add " << n - 81 << endl;
        cin >> x;
    }
    cout << "!" << endl;
    cin >> x;
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
