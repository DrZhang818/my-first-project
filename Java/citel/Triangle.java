import java.util.*;
import java.io.*;

public class Triangle {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int[] a = new int[5];
        for(int i = 1; i <= 4; i++) {
            a[i] = sc.nextInt();
        }
        int tag = 0;
        for(int i = 1; i <= 2; i++) {
            for(int j = i + 1; j <= 3; j++) {
                for(int k = j + 1; k <= 4; k++) {
                    int x = a[i], y = a[j], z = a[k];
                    if(x + y > z && y + z > x && z + x > y) {
                        tag |= 1 << 1;
                    } else if(x + y == z || y + z == x || z + x == y) {
                        tag |= 1;
                    }
                }
            }
        }
        if((tag >> 1 & 1) == 1) {
            out.println("TRIANGLE");
        } else if((tag & 1) == 1) {
            out.println("SEGMENT");
        } else {
            out.println("IMPOSSIBLE");
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