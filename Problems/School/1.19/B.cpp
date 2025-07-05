#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    vector<string> a(n), b(m);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }
    if(n < m){
        cout << "No\n";
        return;
    }
    for(int i = 0; i < n - m + 1; i++){
        for(int j = 0; j < n - m + 1; j++){
            bool ok = true;
            for(int x = i; x < i + m; x++){
                for(int y = j; y < j + m; y++){
                    if(a[x][y] != b[x - i][y - j]){
                        ok = false;
                    }
                }
            }
            if(ok){
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}