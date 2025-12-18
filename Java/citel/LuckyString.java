import java.io.*;
import java.util.*;

public class LuckyString {
    static Scanner sc = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void solve() throws IOException {
        int n = sc.nextInt();
        char[] ch = {'a', 'b', 'c', 'd'};
        for(int i = 0; i < n; i++) {
            int rem = i % 4;
            out.print(ch[rem]);
        }
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