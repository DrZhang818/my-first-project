import java.io.*;
import java.util.*;

class CharStream {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        int cnt = 0;
        long ans = 0;
        for(int i = 1; i <= n; i++) {
            String ss = sc.nextLine();
            if(ss.charAt(0) == '+') {
                cnt++;
            } else if(ss.charAt(0) == '-') {
                cnt--;
            } else {
                char[] s = ss.toCharArray();
                int m = s.length;
                for(int j = 0; j < s.length; j++) {
                    m--;
                    if(s[j] == ':') {
                        break;
                    }
                }
                ans += (long)cnt * m;
            }
        }
        out.println(ans);
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}