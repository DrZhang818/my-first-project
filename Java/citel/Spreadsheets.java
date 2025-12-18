import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Spreadsheets {
    static Scanner sc = new Scanner(System.in);
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    static Pattern pattern = Pattern.compile("R(\\d+)C(\\d+)");

    public static void solve() throws IOException {
        String s = sc.next();
        Matcher matcher = pattern.matcher(s);

        if(matcher.matches()) {
            String row = matcher.group(1);
            String col = matcher.group(2);
            int x = Integer.parseInt(col);
            StringBuilder str = new StringBuilder();
            while(x > 0) {
                x--;
                str.append((char)('A' + x % 26));
                x /= 26;
            }
            out.println(str.reverse() + row);
        } else {
            int idx = 0;
            while(idx < s.length() && !Character.isDigit(s.charAt(idx))) {
                idx++;
            }
            String col = s.substring(0, idx);
            String row = s.substring(idx);
            int x = 0;
            for(char c : col.toCharArray()) {
                x = x * 26 + (c - 'A' + 1);
            }
            out.println("R" + row + "C" + x);
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