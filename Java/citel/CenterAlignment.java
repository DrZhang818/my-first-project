import java.io.*;
import java.util.*;

class CenterAlignment {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        Scanner sc = new Scanner(System.in);
        String[] ss = new String[1005];
        int n = 0;
        int mx = 0;
        while(sc.hasNextLine()) {
            String s = sc.nextLine();
            ss[++n] = s;
            if(s.length() > mx) {
                mx = s.length();
            }
        }
        int len = mx + 2, tag = 0;;
        out.println("*".repeat(len));
        for(int i = 1; i <= n; i++) {
            int sz = ss[i].length();
            int m = len - 2 - sz;
            int x = m / 2, y = m / 2;
            if(m % 2 == 1) {
                if(tag == 0) {
                    y++;
                } else {
                    x++;
                }
                tag ^= 1;
            }
            out.println("*" + " ".repeat(x) + ss[i] + " ".repeat(y) + "*");
        }
        out.println("*".repeat(len));
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}