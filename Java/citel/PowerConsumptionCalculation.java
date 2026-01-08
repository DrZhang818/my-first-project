import java.util.*;
import java.io.*;

public class PowerConsumptionCalculation {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int p1 = sc.nextInt();
        int p2 = sc.nextInt();
        int p3 = sc.nextInt();
        int t1 = sc.nextInt();
        int t2 = sc.nextInt();
        int ans = 0;
        int las = -1;
        for(int i = 1; i <= n; i++) {
            int l = sc.nextInt();
            int r = sc.nextInt();
            ans += (r - l) * p1;
            if(i > 1) {
                int len = l - las;
                if(len <= t1) {
                    ans += len * p1;
                } else if(len <= t1 + t2) {
                    ans += t1 * p1 + (len - t1) * p2;
                } else {
                    ans += t1 * p1 + t2 * p2 + (len - t1 - t2) * p3;
                }
            } 
            las = r;
        }
        out.println(ans);
        out.flush();
    }

}