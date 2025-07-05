#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//无向无权图
void solve1() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

//有向无权图
void solve2() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
}

//无向有权图
void solve3() {
	int n, m;
	cin >> n >> m;
	vector<vector<PII>> adj(n);
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
}

//有向有权图
void solve4() {
	int n, m;
	cin >> n >> m;
	vector<vector<PII>> adj(n);
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		adj[u].emplace_back(v, w);
	}
	for(int i = 0; i < n; i++) {
		for(auto [to, w] : adj[i]) {
			cout << "u: " << i << " v: " << to << " w: " << w << "\n";
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(0);

    solve4();
	return 0;
}