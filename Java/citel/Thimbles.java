import java.io.*;
import java.util.*;

public class Thimbles {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        int n = Integer.parseInt(next());
        int cur = 1;
        for(int i = 0; i < n; i++) {
            String s = next();
            int x = s.charAt(0) - '0';
            int y = s.charAt(2) - '0';
            if(cur == x) {
                cur = y;
            } else if(cur == y) {
                cur = x;
            }
        }
        out.println(cur);
    }

    public static void main(String[] args) throws IOException {
        String tStr = next();
        int t = Integer.parseInt(tStr);
        for(int i = 0; i < t; i++) {
            solve();
        }
        out.flush();
    }

    static String next() throws IOException {
        while(st == null || !st.hasMoreTokens()) {
            String line = br.readLine();
            if(line == null) return null;
            st = new StringTokenizer(line);
        }
        return st.nextToken();
    }
}