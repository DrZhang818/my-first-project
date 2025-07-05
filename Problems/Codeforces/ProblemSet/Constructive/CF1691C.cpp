#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int c1 = 0, c2 = 0, i = 0, j = n - 1;
    while(i < n && s[i] == '0') c1++, i++;
    while(j >= 0 && s[j] == '0') c2++, j--;
    if(j >= 0 && c2 <= k) {
        swap(s[j], s[n - 1]);
        k -= c2;
    }
    if(i < n - 1 && c1 <= k) {
        swap(s[i], s[0]);
    }
    ll sum = 0, cur = 0;
    for(int i = 0; i < n; i++) {
        cur = cur * 10 + s[i] - '0';
        cur %= 100;
        if(i >= 1) sum += cur;
    }
    cout << sum << "\n";
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
    
