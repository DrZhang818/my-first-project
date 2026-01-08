import java.io.*;
import java.util.*;
class Winner {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static void solve() throws IOException {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        String[] s = new String[n + 1];
        int[] a = new int[n + 1];
        for(int i = 1; i <= n; i++) {
            s[i] = sc.next();
            a[i] = sc.nextInt();
        }
        Map<String, Integer> mp = new HashMap<>();
        for(int i = 1; i <= n; i++) {
            mp.merge(s[i], a[i], Integer::sum);
        }
        int mx = Integer.MIN_VALUE;
        for(int x : mp.values()) {
            if(x > mx) {
                mx = x;
            }
        }
        Map<String, Integer> cur = new HashMap<>();
        for(int i = 1; i <= n; i++) {
            if(!mp.get(s[i]).equals(mx)) {
                continue;
            }
            cur.merge(s[i], a[i], Integer::sum);
            if(cur.get(s[i]) == mx) {
                out.println(s[i]);
                return ;
            }
        }
    }
    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}