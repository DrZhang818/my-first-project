import java.io.*;
import java.util.*;

public class TheNOrderedCrosses {
    static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
    
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws IOException {
        int n = nextInt();
        String s = " ".repeat(n) + "*";
        String t = "*".repeat(n << 1 | 1);
        for(int i = 0; i < n; i++) {
            out.println(s);
        }
        out.println(t);
        for(int i = 0; i < n; i++) {
            out.println(s);
        }
        out.flush();
    }

    static int nextInt() throws IOException {
        in.nextToken();
        return (int)in.nval;
    }    
}