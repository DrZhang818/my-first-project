import java.util.*;
import java.io.*;

public class ChessBoard {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    static int n = 8;

    public static void solve() throws IOException {

        String[] a = new String[n];
        for(int i = 0; i < n; i++) {
            a[i] = sc.next();
        }
        int x = 0, y = 0;
        for(int i = 0; i < n; i++) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                char c = a[i].charAt(j);
                if(c == 'B') {
                    cnt++;
                }
            }
            if(cnt == n) {
                x++;
            }
        }
        if(x == n) {
            out.println(n);
            return;
        }
        for(int j = 0; j < n; j++) {
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                char c = a[i].charAt(j);
                if(c == 'B') {
                    cnt++;
                }
            }
            if(cnt == n) {
                y++;
            }
        }
        out.println(x + y);
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}