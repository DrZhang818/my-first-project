#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int c0 = 0, c1 = 0;
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
        c0 += a[i] % 2 == 0;
        c1 += a[i] % 2 == 1;
    }
    int cur = 0, id = 1;
    while(n > 0) {
        if(n % 2 == 0) {
            if(c1 >= n / 2) {
                int sel = -1;
                for(auto &[x, c] : mp) {
                    if(c == 0) continue;
                    if((x - cur) % 2 == 0) {
                        c -= 1;
                        c0 -= 1;
                        n -= 1;
                        sel = x;
                        break;
                    }
                }
                if(sel == -1) {
                    break;
                } else {
                    mp.erase(sel);
                }
            } else {
                cur += 1;
                n -= mp[cur];
                if(cur % 2 == 0) c0 -= mp[cur];
                else c1 -= mp[cur];
                mp.erase(cur);
                swap(c1, c0);
            }
        } else {
            if(c0 >= (n + 1) / 2) {
                int sel = -1;
                for(auto &[x, c] : mp) {
                    if(c == 0) continue;
                    if((x - cur) % 2 == 1) {
                        c -= 1;
                        c1 -= 1;
                        n -= 1;
                        sel = x;
                        break;
                    }
                }
                if(sel == -1) {
                    break;
                } else {
                    mp.erase(sel);
                }
            } else {
                cur += 1;
                n -= mp[cur];
                if(cur % 2 == 0) c0 -= mp[cur];
                else c1 -= mp[cur];
                mp.erase(cur);
                swap(c1, c0);
            }
        }
        id ^= 1;
    }
    if(id == 1) {
        cout << "First\n";
    } else {
        cout << "Second\n";        
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
