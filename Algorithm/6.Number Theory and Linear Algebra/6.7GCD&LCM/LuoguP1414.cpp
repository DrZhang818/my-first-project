#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<int> cnt(1000005);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mx = x > mx ? x : mx;
        for(int i = 1; i * i <= x; i++) {
            if(x % i == 0) {
                cnt[i]++;
                if(i * i != x) {
                    cnt[x / i]++;
                }
            }
        }
    }
    for(int i = 1, j = mx; i <= n; i++) {
        while(cnt[j] < i) j--;
        cout << j << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
