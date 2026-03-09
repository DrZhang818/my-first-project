#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    i64 x;
    cin >> x;

    if(x < 10) {
        cout << 0 << "\n";
        return;
    }

    vector<int> a;
    int sum = 0;
    while(x >= 10) {
        a.push_back(x % 10);
        sum += x % 10;
        x /= 10;
    }
    sum += x;

    sort(a.begin(), a.end(), greater<int>());
    int t = sum;

    int ans1 = 0, ans2 = 0;
    for(int y : a) {
        if(sum >= 10) {
            sum -= y;
            ans1++;
        } else {
            break;
        }
    }

    if(x == 1) {
        cout << ans1 << "\n";
        return;
    }

    sum = t;

    ans2 = 1;
    sum -= x;
    sum += 1;

    for(int y : a) {
        if(sum >= 10) {
            sum -= y;
            ans2++;
        } else {
            break;
        }
    }

    cout << min(ans1, ans2) << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
