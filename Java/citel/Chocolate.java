import java.util.*;
import java.io.*;

public class Chocolate {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int n = sc.nextInt();
        int[] a = new int[n + 1];
        for(int i = 1; i <= n; i++) {
            a[i] = sc.nextInt();
        }
        int na = 0, nb = 0;
        int l = 1, r = n;
        int tag = 0;
        while(l <= r) {
            if(l == r) {
                if(tag == 1) {
                    nb++;
                    r--;
                } else {
                    na++;
                    l++;
                }
            } else {
                int x = Math.min(a[l], a[r]);
                a[l] -= x;
                a[r] -= x;
                tag = 1;
                if(a[l] == 0) {
                    l++;
                    na++;
                }
                if(a[r] == 0) {
                    r--;
                    nb++;
                    tag = 0;
                }
            }
        }
        out.println(na + " " + nb);
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}