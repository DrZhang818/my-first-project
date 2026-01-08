import java.io.*;
import java.util.*;
class RegistrationSystem {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer st;
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static void solve() throws IOException {
        int n = Integer.parseInt(next());
        Map<String, Integer> mp = new HashMap<>();
        for(int i = 1; i <= n; i++) {
            String s = next();
            int v = mp.getOrDefault(s, 0);
            if(v == 0) {
                out.println("OK");
            } else {
                out.println(s + v);
            }
            mp.merge(s, 1, Integer::sum);
        }
    }
    public static void main(String[] args) throws IOException {
        solve();
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