#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

class my_deque{
private:
    vector<int> m_deque;
    int l, r, s, limit;
public:
    my_deque(int capecity = 10000){
        m_deque.resize(capecity);
        l = r = s = 0;
        limit = capecity;
    }
    void push_front(int a){
        if(full()){
            cout << "Deque is already full!";
        }else{
            if(empty()){
                l = r = 0;
                m_deque[0] = a;
            }else{
                l = l == 0 ? limit - 1 : l - 1;
                m_deque[l] = a;
            }
            s++;
        }
    }
    void push_back(int a){
        if(full()){
            cout << "Deque is already full!";
        }else{
            if(empty()){
                l = r = 0;
                m_deque[0] = a;
            }else{
                r = r == limit - 1 ? 0 : r + 1;
                m_deque[r] = a;
            }
            s++;
        }
    }
    void pop_front(){
        if(empty()){
            cout << "No Element!";
        }
        s--;
        l = l == limit - 1 ? 0 : l + 1;
    }
    void pop_back(){
        if(empty()){
            cout << "No Element!";
        }
        s--;
        r = r == 0 ? limit - 1 : r - 1;
    }
    int get_front(){
        if(empty()){
            cout << "No Element!";
            return -1;
        }
        return m_deque[l];
    }
    int get_back(){
        if(empty()){
            cout << "No Element!";
            return -1;
        }
        return m_deque[r];
    }
    int size(){
        return s;
    }
    bool empty(){
        return s == 0;
    }
    bool full(){
        return s == limit;
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    my_deque dq(100);
    dq.push_front(4);
    dq.push_back(46);
    dq.push_front(14);
    dq.push_back(1000);
    while(!dq.empty()){
        cout << dq.get_front() << " ";
        dq.pop_front();
    }

    return 0;
}
