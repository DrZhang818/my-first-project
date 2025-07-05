#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct node{
	int id, pre, nxt;
	node(int x = 0, int p = 0, int n = 0) : id(x), pre(p), nxt(n) {}
};
class List{
private:
	vector<node> a;
	vector<bool> vis;
	int size;
public:
	List(int n) {
		a.resize(n);
		vis.resize(n, false);
		size = 0;
	}
	void ins_back(int x, int y) {
		a[++size] = node(y, x, a[x].nxt);
		a[a[x].nxt].pre = size;
		a[x].nxt = size;
	}

	void ins_front(int x, int y) {
		a[++size] = node(y, a[x].pre, x);
		a[a[x].pre].nxt = size;
		a[x].pre = size;
	}
	void erase(int x) {
		if(vis[x]) return;
		int lt = a[x].pre, rt = a[x].nxt;
		a[lt].nxt = rt;
		a[rt].pre = lt;
		vis[x] = true;
	}
	void print() {
		int cur = a[0].nxt;
		while(cur) {
			cout << a[cur].id << " ";
			cur = a[cur].nxt;
		}
		cout << "\n";
	}
};
void solve(){
	int n;
	cin >> n;
	List lst(n + 2);
	lst.ins_back(0, 1);
	for(int i = 2; i <= n; i++) {
		int k, p;
		cin >> k >> p;
		if(p == 1) {
			lst.ins_back(k, i);
		}else {
			lst.ins_front(k, i);
		}
	}
	int m;
	cin >> m;
	for(int i = 0; i < m; i++){
		int x;
		cin >> x;
		lst.erase(x);
	}
	lst.print();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

