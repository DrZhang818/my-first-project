class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int l = -1, p = -1;
        int c = 0, mn = INT_MAX, mx = INT_MIN;
        if(!head->next || !head->next->next) {
            return {-1, -1};
        }
        auto check = [&](int a, int b, int c) -> bool{
            return (b > a && b > c) || (b < a && b < c);
        };
        ListNode *pre = head, *cur = pre->next, *nxt = cur->next;
        while(nxt) {
            if(check(pre->val, cur->val, nxt->val)) {
                if(p == -1) {
                    p = c;
                    l = p;
                }
                else{
                    mx = c - l;
                    mn = min(mn, c - p);
                    p = c;
                }
            }
            c++;
            pre = cur;
            cur = nxt;
            nxt = nxt->next;
        }
        if(mn == INT_MAX) {
            return {-1, -1};
        }
        return {mn, mx};
    }
};