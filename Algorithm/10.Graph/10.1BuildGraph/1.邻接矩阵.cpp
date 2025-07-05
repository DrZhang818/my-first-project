#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//无向带权图
void solve1() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> Graph(n, vector<int>(n));
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		Graph[u][v] = w;
		Graph[v][u] = w;
	}
}

//有向带权图
void solve2() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> Graph(n, vector<int>(n));
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		Graph[u][v] = w;
	}
}
