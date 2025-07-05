#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


// void solve(){
// 	int n;
// 	cin >> n;
// 	vector<bool> vis(n, false);
// 	vector<string> ss(n);
// 	vector<ll> hashs(n);
// 	for(int i = 0; i < n; i++){
// 		cin >> ss[i];
// 	}
// 	const int base = 11;
// 	const int mod = 1000000007;
// 	vector<int> to(26);
// 	for(ll i = 0, cur = 1; i < 26; i++){
// 		to[i] = cur;
// 		cur = base * cur % mod;
// 	}
// 	for(int i = 0; i < n; i++){
// 		ll cur = 0;
// 		for(char c : ss[i]){
// 			c -= 'a';
// 			cur = (to[c] + cur) % mod;
// 		}
// 		hashs[i] = cur;
// 	}
// 	ll ans = 0;
// 	unordered_map<ll, int> cnt;
// 	for(int i = 0; i < n; i++){
// 		ans += cnt[hashs[i]];
// 		cnt[hashs[i]]++;
// 	}
// 	cout << ans << "\n";
// }

void solve(){
	int n;
	cin >> n;
	map<string, int> mp;
	ll ans = 0;
	for(int i = 0; i < n; i++){
		string s;
		cin >> s;
		sort(s.begin(), s.end());
		ans += mp[s];
		mp[s]++;
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