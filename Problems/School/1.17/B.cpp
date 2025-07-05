#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
	int n, m;
	cin >> n >> m;
	vector<PII> stu(n), check(m);
	for(int i = 0; i < n; i++){
		cin >> stu[i].first >> stu[i].second;
	}	
	for(int i = 0; i < m; i++){
		cin >> check[i].first >> check[i].second;
	}
	for(int i = 0; i < n; i++){
		int x = stu[i].first, y = stu[i].second;
		int idx = 0, cur = INT_MAX;
		for(int j = 0; j < m; j++){
			if(abs(check[j].first - x) + abs(check[j].second - y) < cur){
				idx = j;
				cur = abs(check[j].first - x) + abs(check[j].second - y);
			}
		}
		cout << idx + 1 << "\n";
	}
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}