#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;



string Manacher(const string &s){
	string T = "#";
	for(char c : s){
		T += c;
		T += '#';
	}
	int n = T.size();
	vector<int> P(n, 0);
	for(int i = 0, c = 0, r = 0, len; i < n; i++){
		len = r > i ? min(P[2 * c - i], r - i) : 1;
		while(i + len < n && i - len >= 0 && T[i + len] == T[i - len]){
			len++;
		}
		if(i + len > r){
			r = i + len;
			c = i;
		}
		P[i] = len;
	}
	int mx = 1, idx = 0;
	for(int i = 0; i < n; i++){
		cout << P[i] << " ";
		if(P[i] > mx){
			mx = P[i];
			idx = i;
		}
	}
	cout << "\n";
	mx -= 1;
	int start = (idx - mx) / 2;
	return s.substr(start, mx);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;
	string ans = Manacher(s);
	cout << ans.size() << "\n" << ans << "\n";
	return 0;
}