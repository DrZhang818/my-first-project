import java.util.*;
import java.io.*;

public class AplusB {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    static long a, b;

    public static void solve() throws IOException {
        int[] A = new int[15];
        int[] B = new int[15];
        int idx1 = 0, idx2 = 0;
        while(a > 0) {
            A[++idx1] = (int)(a % 10);
            a /= 10;
        }
        while(b > 0) {
            B[++idx2] = (int)(b % 10);
            b /= 10;
        }
        int cnt = 0;
        for(int i = 0, carry = 0; i < 10; i++) {
            int t = A[i] + B[i] + carry;
            if(t >= 10) {
                cnt++;
                carry = 1;
            } else {
                carry = 0;
            }
        }
        if(cnt == 0) {
            out.println("No carry operation.");
            return;
        }
        if(cnt == 1) {
            out.println("1 carry operation.");
            return;
        }
        out.printf("%d carry operations.\n", cnt);
    }

    public static void main(String[] args) throws IOException {
        while(true) {
            a = sc.nextLong();
            b = sc.nextLong();
            if(a == 0 && b == 0) {
                break;
            }
            solve();
        }
        out.flush();
    }
}