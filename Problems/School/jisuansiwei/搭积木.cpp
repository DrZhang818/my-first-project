#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;



int n;
vector<stack<int>> a;
vector<int> pos;
void init(int x) {
    int p = pos[x];
    while(a[p].top() != x) {
        int u = a[p].top();
        a[p].pop();
        a[u].push(u);
        pos[u] = u;
    }
}
void op1(int u, int v) {
    init(u);
    init(v);
    a[pos[u]].pop();
    a[pos[v]].push(u);
    pos[u] = pos[v];
}
void op2(int u, int v) {
    init(u);
    a[pos[u]].pop();
    a[pos[v]].push(u);
    pos[u] = pos[v];
} 
void op3(int u, int v) {
    init(v);
    stack<int> t;
    while(a[pos[u]].top() != u) {
        int w = a[pos[u]].top();
        a[pos[u]].pop();
        t.push(w);
        pos[w] = pos[v];
    }
    a[pos[u]].pop();
    pos[u] = pos[v];
    t.push(u);
    while(!t.empty()) {
        a[pos[v]].push(t.top());
        t.pop();
    }
}
void op4(int u, int v) {
    stack<int> t;
    while(a[pos[u]].top() != u) {
        int w = a[pos[u]].top();
        a[pos[u]].pop();
        t.push(w);
        pos[w] = pos[v];
    }
    a[pos[u]].pop();
    pos[u] = pos[v];
    t.push(u);
    while(!t.empty()) {
        a[pos[v]].push(t.top());
        t.pop();
    }
}
void op5(int u, int v) {
    stack<int> t1 = a[pos[u]], t2 = a[pos[v]];
    int len1 = t1.size(), len2 = t2.size();
    int tpu = pos[u], tpv = pos[v];
    while(len1--) {
        int w = t1.top();
        t1.pop();
        pos[w] = tpv;
    }
    while(len2--) {
        int w = t2.top();
        t2.pop();
        pos[w] = tpu;
    }
    swap(a[tpu], a[tpv]);
}
void solve() {
    cin >> n;
    cin.ignore();
    a.resize(n); 
    pos.resize(n);
    for(int i = 0; i < n; i++) a[i].push(i);
    iota(pos.begin(), pos.end(), 0);
    string s;
    while(getline(cin, s)) {
        if(s == "q") break;
        istringstream ss(s);
        vector<string> tokens(4);
        for(int i = 0; i < 4; i++) {
            ss >> tokens[i];
        }   
        int u = stoi(tokens[1]), v = stoi(tokens[3]);  
        if(pos[u] == pos[v]) continue;
        if(tokens[0] == "mv") {
            if(tokens[2] == "on") {
                op1(u, v);
            } else {
                op2(u, v);
            }
        } 
        else if(tokens[0] == "st") {
            if(tokens[2] == "on") {
                op3(u, v);
            } else {
                op4(u, v);
            }
        } 
        else {
            op5(u, v);
        }
    }
    for(int i = 0; i < n; i++) {
        cout << i << ":";
        stack<int> t;
        while(!a[i].empty()) {
            t.push(a[i].top());
            a[i].pop();
        }
        while(!t.empty()) {
            cout << " " << t.top();
            t.pop();
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
