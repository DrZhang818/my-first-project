import java.io.*;
import java.util.*;

public class LuckySumofDigits {
    static Scanner sc = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void solve() throws IOException {
        int n = sc.nextInt();
        int c4 = -1, c7 = -1;
        for(int i = 0; i * 4 <= n; i++) {
            int x = n - i * 4;
            if(x % 7 != 0) continue;
            c4 = i;
            c7 = x / 7;
            break;
        }
        if(c4 == -1) {
            out.println(-1);
            return;
        }
        for(int i = 0; i < c4; i++) out.print(4);
        for(int i = 0; i < c7; i++) out.print(7);
        out.println();
    }

    public static void main(String[] args) throws IOException {
        int t = sc.nextInt();
        while(t-- > 0) {
            solve();
        }
        out.flush();
    }    

}