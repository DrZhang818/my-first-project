#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Myqueue {
private:
    vector<int> data;
    int cap;
    int head, rear;
public:
    Myqueue(int n) {
        data.resize(n);
        cap = n;
        head = rear = 0;
    }
    int size() {
        return (rear - head + cap) % cap;
    }
    bool empty() {
        return size() == 0;
    }
    bool push(int x) {
        if((rear + 1) % cap == head) return false;
        data[rear] = x;
        rear = (rear + 1) % cap;
        return true;
    }
    bool pop() {
        if(head == rear) return false;
        head = (head + 1) % cap;
        return true;
    }
    int front() {
        return data[head];
    }
};
void solve(){
    int m, n;
    cin >> m >> n;
    Myqueue q(m + 1);
    unordered_map<int,int> mp;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(!mp[x]) {
            ans++;
            if(q.size() == m) {
                mp[q.front()]--;
                q.pop();
            }
            q.push(x);
            mp[x]++;
        }
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

