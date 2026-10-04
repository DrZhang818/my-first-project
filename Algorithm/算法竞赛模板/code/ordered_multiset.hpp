#pragma once
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T> struct OrderedSet {
    using Key = pair<T, int>;
    tree<Key, null_type, less<Key>, rb_tree_tag, tree_order_statistics_node_update> tr;
    int uid = 0;
    int size() const {
        return int(tr.size());
    }
    void insert(const T& x) {
        tr.insert({x, uid++});
    }
    bool erase(const T& x) {
        auto it = tr.lower_bound({x, numeric_limits<int>::min()});
        if(it == tr.end() || it->first != x) {
            return false;
        }
        tr.erase(it);
        return true;
    }
    int orderOfKey(const T& x) const {
        return int(tr.order_of_key({x, numeric_limits<int>::min()}));
    }
    int count(const T& x) const {
        return int(tr.order_of_key({x, numeric_limits<int>::max()})) - orderOfKey(x);
    }
    bool kth(int k, T& ans) const {
        if(k < 1 || k > size()) {
            return false;
        }
        ans = tr.find_by_order(k - 1)->first;
        return true;
    }
};
