import java.util.*;
import java.io.*;

public class SuperAgent {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() {
        char[][] a = new char[3][3];
        for(int i = 0; i < 3; i++) {
            a[i] = sc.next().toCharArray();
        }

        boolean ok = true;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(a[i][j] != a[2 - i][2 - j]) {
                    ok = false;
                    break;
                }
            }
        }

        if(ok) {
            out.println("YES");
        } else {
            out.println("NO");
        }
    }

    public static void main(String[] args) {
        solve();
        out.flush();
        out.close();
    }
}