import java.util.*;
import java.io.*;

public class JumpingJack {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        long x = sc.nextLong();
        if(x < 0) {
            x = -x;
        }
        long k = ((long)(Math.sqrt(1 + 8 * x) - 1)) / 2;
        while(k * (k + 1) / 2 < x || k * (k + 1) / 2 % 2 != x % 2) {
            k++;
        }
        out.println(k);
    }

    public static void main(String[] args) throws IOException {
        int t = sc.nextInt();
        while(t-- > 0) {
            solve();
        }
        out.flush();
    }
}