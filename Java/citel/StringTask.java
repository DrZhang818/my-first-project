import java.util.*;
import java.io.*;

public class StringTask {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    static String S = "aoyeui";

    public static void solve() throws IOException {
        String s = sc.next();
        StringBuilder ans = new StringBuilder();

        for(char c : s.toCharArray()) {
            c = Character.toLowerCase(c);
            if(S.indexOf(c) != -1) {
                continue;
            }
            ans.append('.');
            ans.append(c);
        }
        out.println(ans.toString());
    }

    public static void main(String[] args) throws IOException {
        int t = 1;
        // t = sc.nextInt();
        while(t-- > 0) {
            solve();
        }
        out.flush();
    }
}