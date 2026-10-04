#pragma once
#include <bits/stdc++.h>
using namespace std;
struct TwoSAT {
    int n;
    vector<vector<int>> adj;
    vector<bool> answer;
    vector<int> dfn, low, stack, id;
    vector<bool> inStack;
    int timer = 0, count = 0;
    TwoSAT(int n_ = 0)
        : n(n_), adj(2 * n_ + 2), answer(n_ + 1), dfn(2 * n_ + 2), low(2 * n_ + 2),
          id(2 * n_ + 2, -1), inStack(2 * n_ + 2) {
    }
    int literal(int x, bool value) const {
        return 2 * x + int(value);
    }
    void imply(int a, int b) {
        adj[a].push_back(b);
    }
    void addClause(int x, bool xValue, int y, bool yValue) {
        int a = literal(x, xValue);
        int b = literal(y, yValue);
        imply(a ^ 1, b);
        imply(b ^ 1, a);
    }
    void setValue(int x, bool value) {
        addClause(x, value, x, value);
    }
    bool solve() {
        timer = count = 0;
        stack.clear();
        fill(dfn.begin(), dfn.end(), 0);
        fill(low.begin(), low.end(), 0);
        fill(inStack.begin(), inStack.end(), false);
        for(int u = 2; u <= 2 * n + 1; u++) {
            if(!dfn[u]) {
                dfs(u);
            }
        }
        for(int i = 1; i <= n; i++) {
            if(id[2 * i] == id[2 * i + 1]) {
                return false;
            }
            answer[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }

  private:
    void dfs(int s) {
        vector<pair<int, int>> cs{{s, 0}};
        dfn[s] = low[s] = ++timer;
        stack.push_back(s);
        inStack[s] = true;
        while(!cs.empty()) {
            int u = cs.back().first;
            int& i = cs.back().second;
            if(i < int(adj[u].size())) {
                int v = adj[u][i++];
                if(!dfn[v]) {
                    dfn[v] = low[v] = ++timer;
                    stack.push_back(v);
                    inStack[v] = true;
                    cs.push_back({v, 0});
                } else if(inStack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            } else {
                cs.pop_back();
                if(low[u] == dfn[u]) {

                    while(true) {
                        int v = stack.back();
                        stack.pop_back();
                        inStack[v] = false;
                        id[v] = count;
                        if(v == u) {
                            break;
                        }
                    }
                    count++;
                }
                if(!cs.empty()) {
                    int p = cs.back().first;
                    low[p] = min(low[p], low[u]);
                }
            }
        }
    }
};
