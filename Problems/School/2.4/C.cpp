#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, k;
    cin >> n >> k;
    map<int, int> mp;
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    auto check = [&](int x) ->bool {
        int t = x;
        while(t) {
            int pop = t % 10;
            if(mp[pop] != 0) {
                return false;
            }
            t /= 10;
        }
        return true;
    };
    while(!check(n)) n++;
    cout << n << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

