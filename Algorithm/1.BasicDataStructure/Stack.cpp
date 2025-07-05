#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class MyStack{
private:
    vector<int> a;
    int tot;
public:
    MyStack(int n) {
        a.resize(n);
    }
    void push(int x) { a[++tot] = x; }
    int top() { return a[tot]; }
    void pop() { tot--; }
    bool empty() { return tot == 0; } 
};
