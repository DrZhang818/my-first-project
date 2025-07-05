#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



//优化解法
void solve(){
	vector<ll> C(61);
	int n, m;
	cin >> n >> m;
	C[0] = 1;
	for(int i = 1; i <= m; i++){
		C[i] = C[i - 1] * (m - i + 1) / i;
	} 
	ll ans = 0;
	for(int i = n; i <= m; i++){
		ans += C[i];
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