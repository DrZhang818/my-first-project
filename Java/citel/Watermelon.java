import java.util.*;
import java.io.*;

public class Watermelon {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int n = sc.nextInt();
        if(n > 2 && n % 2 == 0) {
            out.println("YES");
        } else {
            out.println("NO");
        }
    }

    public static void main(String[] args) throws IOException {
        int t = sc.nextInt();
        while(t-- > 0) {
            solve();
        }
        out.flush();
    }
}