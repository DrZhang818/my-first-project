import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Main {
    static Scanner sc = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    static Pattern p = Pattern.compile("(-?\\d+)");

    public static void solve() throws IOException {
        String s = sc.nextLine();
        Matcher m = p.matcher(s);
        while(m.find()) {
            out.println(m.group(1));
        }
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }    

}