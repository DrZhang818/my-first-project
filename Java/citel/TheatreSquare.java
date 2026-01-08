import java.util.*;
import java.io.*;

public class TheatreSquare {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int n = sc.nextInt();
        int m = sc.nextInt();
        int a = sc.nextInt();
        long ans = 0;
        long x = (n + a - 1) / a;
        long y = (m + a - 1) / a;
        ans = x * y;
        out.println(ans);
    }

    public static void main(String[] args) throws IOException {
        int t = sc.nextInt();
        while(t-- > 0) {
            solve();
        }
        out.flush();
    }
}