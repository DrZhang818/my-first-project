#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
	int n, x;
	cin >> n >> x;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	queue<int> q;
	ll ans = 0;
	for(auto c : a){
		while(!q.empty() && c > q.front()){
			q.pop();
		}
		q.push(c + x);
		ans = max(ans, (ll)q.size());
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