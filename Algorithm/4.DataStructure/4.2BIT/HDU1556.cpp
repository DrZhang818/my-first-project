#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class BIT {
private:
    vector<int> a;
    int n;
public:
    BIT(int x) {
        a.resize(x + 1);
        n = x;
    }
    void add(int i, int x) {
        while(i <= n) {
            a[i] += x;
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res += a[i];
            i -= i & -i;
        }
        return res;
    }
};
void solve(int n) { 
    BIT tree(n);
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree.add(a, 1);
        tree.add(b + 1, -1);
    }
    for(int i = 1; i <= n; i++) {
        cout << tree.query(i) << " \n"[i == n];
    }
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin >> n && n) {
        solve(n);
    }
    return 0;
}
    
