import java.io.*;
import java.util.*;

public class NearlyLuckyNumber {
    static Scanner sc = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void solve() throws IOException {
        long num = sc.nextLong();
        int c = 0;
        while(num > 0) {
            int rem = (int)(num % 10);
            num /= 10;
            if(rem == 4 || rem == 7) {
                c++;
            }
        }
        if(c == 4 || c == 7) {
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