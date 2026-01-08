import java.util.*;
import java.io.*;

public class IncreasingSequence {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int n = sc.nextInt();
        int d = sc.nextInt();
        long[] a = new long[n + 1];
        for(int i = 1; i <= n; i++) {
            a[i] = sc.nextLong();
        }
        long ans = 0;
        for(int i = 2; i <= n; i++) {
            if(a[i] > a[i - 1]) continue;
            long x = a[i - 1] - a[i];
            long t = x / d + 1;
            a[i] += t * d;
            ans += t;
        }
        out.println(ans);
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}