#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    deque<int> q;
    for(int i = 0; i < n; i++) {
        while(!q.empty() && q.front() < i - m) {
            q.pop_front();
        }
        if(q.empty()) {
            cout << 0 << "\n";
        } else {
            cout << a[q.front()] << "\n";
        }
        while(!q.empty() && a[q.back()] >= a[i]) {
            q.pop_back();
        }
        q.push_back(i);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

