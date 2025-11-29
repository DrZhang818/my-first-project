class IsSubString {
    IsSubString() {}
    public static boolean isSubString(String s, String t) {
        int n = s.length(), m = t.length();
        int[] nxt = new int[n + 1];
        for(int i = 1; i < n; i++) {
            int j = nxt[i];
            while(j != 0 && s.charAt(i) != s.charAt(j)) j = nxt[j];
            nxt[i + 1] = (s.charAt(i) == s.charAt(j) ? j + 1 : 0);
        }
        for(int i = 0, j = 0; i < m; i++) {
            while(j != 0 && t.charAt(i) != s.charAt(j)) j = nxt[j];
            if(t.charAt(i) == s.charAt(j)) {
                j++;
            }
            if(j == n) {
                return true;
            }
        }
        return false;
    }
}