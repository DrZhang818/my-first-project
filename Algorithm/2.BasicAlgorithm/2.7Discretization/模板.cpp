#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct info {
    int val;
    int id;
};
void solve(){ 
    int n;
    cin >> n;

    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a.begin() + 1, a.end(), [](auto &a, auto &b) -> bool{ 
        return a.val < b.val;
    });
    for(int i = 1; i <= n; i++) {
        cout << a[i].val << " \n"[i == n];
    }
    vector<int> na(n + 1);
    for(int i = 1; i <= n; i++) {
        na[a[i].id] = i;
    }
    for(int i = 1; i <= n; i++) {
        cout << na[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

