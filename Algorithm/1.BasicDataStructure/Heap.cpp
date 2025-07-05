#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Heap{
private:
    vector<int> heap;
    int len;
public:
    Heap(int n) {
        heap.resize(n, 0);
        len = 0;
    }
    void push(int x) {
        heap[++len] = x;
        int i = len;
        while(i > 1 && heap[i >> 1] > heap[i]) {
            swap(heap[i >> 1], heap[i]);
            i >>= 1;
        }
    }
    void pop() {
        heap[1] = heap[len--];
        int i = 1;
        while((i << 1) <= len) {
            int son = (i << 1);
            if(son < len && heap[i << 1 | 1] < heap[i << 1]) {
                son = (i << 1 | 1);
            }
            if(heap[son] < heap[i]) {
                swap(heap[son], heap[i]);
                i = son;
            } 
            else break;
        }
    }
    int top() {
        return heap[1];
    }
};

void solve() {
    int n;
    cin >> n;
    Heap pq(n + 1);
    for(int i = 0; i < n; i++) {
        int flag;
        cin >> flag;
        if(flag == 1) { 
            int x;
            cin >> x;
            pq.push(x);
        }
        else if(flag == 2) {
            cout << pq.top() << "\n";
        }
        else {
            pq.pop();
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}