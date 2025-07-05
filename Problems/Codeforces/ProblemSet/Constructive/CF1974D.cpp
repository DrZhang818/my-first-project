#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1974/D
void solve() { 
    int n;
    cin >> n;
    string s;
    cin >> s;
    int c1 = 0, c2 = 0;
    for(int i = 0; i < n; i++) {
        int t;
        if(s[i] == 'N' || s[i] == 'S') {
            c1 += s[i] == 'N' ? 1 : -1;
        } else {
            c2 += s[i] == 'E' ? 1 : -1;
        }
    }
    if(c1 % 2 != 0 || c2 % 2 != 0) {
        cout << "NO\n";
        return;
    }
    if(!c1 && !c2 && n <= 2) {
        cout << "NO\n";
        return;
    }
    c1 /= 2;
    c2 /= 2;
    for(int i = 0; i < n; i++) {
        int t;
        if(s[i] == 'N' || s[i] == 'S') {
            t = s[i] == 'N' ? 1 : -1;
            if(i == 0 || c1 * t > 0) {
                c1 -= t;
                cout << "R";
            } else {
                cout << "H";
            }
        } else {
            t = s[i] == 'E' ? 1 : -1;
            if(i == 0 || c2 * t > 0) {
                c2 -= t;
                cout << "R";
            } else {
                cout << "H";
            }
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
