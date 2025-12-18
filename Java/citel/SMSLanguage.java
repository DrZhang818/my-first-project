import java.util.*;
import java.io.*;

class SMSLanguage {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        String s = br.readLine();
        s = s.replace(".", "")
             .replace(",", "")
             .replace("?", "")
             .replace("!", "");
        s = s.toLowerCase();
        s = s.replace("and", "&");
        s = s.replace("ate", "8");
        s = s.replace("at", "@");
        s = s.replace("you", "U");
        out.println(s);
    }

    public static void main(String[] args) throws IOException {
        String line = br.readLine();
        int t = Integer.parseInt(line.trim());
        while(t-- > 0) {
            solve();
        }
        out.flush();
    }

}