#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



//无向无权图
void solve1() {
	int n, m;
	cin >> n >> m;
	struct Node {
		int to, next;
	};
	vector<int> head(n, -1);
	vector<Node> nodes(2 * m);
	int cnt = 0;
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		nodes[cnt] = {v, head[u]};
		head[u] = cnt++;
		nodes[cnt] = {u, head[v]};
		head[v] = cnt++;
	}
	//遍历
	for(int u = 0; u < n; u++) {
		for(int cur = head[u]; cur != -1; cur = nodes[cur].next) {
			int v = nodes[cur].to;
		}
	}
}

//有向无权图
void solve2() {
	int n, m;
	cin >> n >> m;
	struct Node {
		int to, next;
	};
	vector<int> head(n, -1);
	vector<Node> nodes(m);
	int cnt = 0;
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		nodes[i] = {v, head[u]};
		head[u] = i;
	}
	//遍历
	for(int u = 0; u < n; u++) {
		for(int cur = head[u]; cur != -1; cur = nodes[cur].next) {
			int v = nodes[cur].to;
		}
	}
}

//无向有权图
void solve3() {
	int n, m;
	cin >> n >> m;
	struct Node {
		int to, next, w;
	};
	vector<int> head(n, -1);
	vector<Node> nodes(2 * m);
	int cnt = 0;
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		nodes[cnt] = {v, head[u], w};
		head[u] = cnt++;
		nodes[cnt] = {u, head[v], w};
		head[v] = cnt++;
	}
}

//有向有权图
void solve4() {
	int n, m;
	cin >> n >> m;
	struct Node {
		int to, next, w;
	};
	vector<int> head(n, -1);
	vector<Node> nodes(m);
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		nodes[i] = {v, head[u], w};
		head[u] = i;
	}
	for(int u = 0; u < n; u++) {
		for(int cur = head[u]; cur != -1; cur = nodes[cur].next) {
			int v = nodes[cur].to;
			int w = nodes[cur].w;
			cout << "u: " << u << " v: " << v << " w: " << w << "\n"; 
		}
	}
}

int main() {
	solve4();
	return 0;
}
