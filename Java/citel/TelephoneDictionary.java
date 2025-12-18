import java.io.*;
import java.util.*;

public class TelephoneDictionary {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        int n = Integer.parseInt(next());
        Map<String,Integer> mp = new TreeMap<>();
        for(int i = 1; i <= n; i++) {
            String s = next();
            s = work(s);
            mp.merge(s, 1, Integer::sum);
        }
        mp.forEach((s, c) -> {
            if(c > 1) {
                out.println(s + " " + c);
            }
        });
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }

    static String work(String s) {
        StringBuilder res = new StringBuilder();
        for(char c : s.toCharArray()) {
            if(c == '-') continue;
            if(res.length() == 3) {
                res.append('-');
            }
            if('0' <= c && c <= '9') {
                res.append(c);
            } else {
                res.append(get(c));
            }
        }
        return res.toString();
    }

    static int get(char c) {
        if(c <= 'C') return 2;
        if(c <= 'F') return 3;
        if(c <= 'I') return 4;
        if(c <= 'L') return 5;
        if(c <= 'O') return 6;
        if(c <= 'S') return 7;
        if(c <= 'V') return 8;
        return 9;
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