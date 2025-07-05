#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    int l = (n + 1) / 2, r = l + (n % 2 == 0), cnt = 0;
    char c = s[l];
    while(l >= 1 && r <= n) {
        if(s[l--] == c && s[r++] == c) {
            cnt++;
        } else {
            break;
        }
    }
    cout << n / 2 + cnt << "\n"; 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
