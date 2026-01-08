import java.util.*;
import java.io.*;

public class AplusB {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int n = sc.nextInt();
        for(int i = 0; i <= 2 * n; i++) {
            int j = Math.min(i, 2 * n - i);
            out.print(" ".repeat(2 * (n - j)));
            for(int k = 0; k < 2 * j + 1; k++) {
                int x = Math.min(k, 2 * j - k);
                out.print(x + " ");
            }
            out.println();
        }
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}