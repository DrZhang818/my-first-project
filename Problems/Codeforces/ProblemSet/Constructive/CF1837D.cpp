#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//  66

// )(()(((()))()()(())))((()))))(()(()(())))()()(()(())((()))(())((()

void solve() { 
    int n;
    string s;
    cin >> n >> s;
    vector<int> a(n);
    bool st = false;
    int flag, c1, c2, k = 0;
    c1 = c2 = 0;
    for(int i = 0; i < n; i++) {
        c1 += s[i] == '(';
        c2 += s[i] == ')';
        if(!st || flag == 1 && c2 > c1 || flag == 2 && c1 > c2) {
            st = true;
            flag = s[i] == '(' ? 1 : 2;
            c1 = s[i] == '(';
            c2 = s[i] == ')';
            k += 1;
        } 
        a[i] = flag;
    }
    if(c1 != c2) {
        cout << -1 << "\n";
        return;
    }
    k = min(2, k);
    cout << k << "\n";
    for(int i = 0; i < n; i++) {
        cout << min(k, a[i]) << " \n"[i == n - 1];
    }
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
    
