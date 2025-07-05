#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int to[10] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};
    int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    auto check1 = [&](int x) -> bool {
        int d = x % 100;
        x /= 100;
        int m = x % 100;
        x /= 100;
        int y = x;
        int lim = day[m];
        if(m <= 0 || m >= 13 || d == 0) return false;
        if(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
            if(m == 2) {
                lim += 1;
            }
        }
        return d <= lim;
    };
    auto check2 = [&](int x) -> bool {
        int res = 0;
        while(x) {
            int pop = x % 10;
            x /= 10;
            res += to[pop];
        }
        return res > 50;
    };
    int ans = 0;
    for(int i = 20000101; i <= 20240413; i++) {
        if(check1(i)) {
            if(check2(i)) {
                ans += 1;
            }
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
