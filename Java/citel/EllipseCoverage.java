import java.io.*;
import java.util.*;

public class EllipseCoverage {
    static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
    
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        int x1 = nextInt();
        int y1 = nextInt();
        int x2 = nextInt();
        int y2 = nextInt();
        int d = nextInt();
        int ans = 0;
        for(int x = -300; x <= 300; x++) {
            for(int y = -300; y <= 300; y++) {
                double dis1 = Math.sqrt(Math.pow(x - x1, 2) + Math.pow(y - y1, 2));
                double dis2 = Math.sqrt(Math.pow(x - x2, 2) + Math.pow(y - y2, 2));
                if(dis1 + dis2 < d) {
                    ans++;
                }
            }
        }
        out.println(ans);
    }

    public static void main(String[] args) throws IOException {
        int t = nextInt();
        for(int i = 0; i < t; i++) {
            solve();
        }
        out.flush();
    }

    static int nextInt() throws IOException {
        in.nextToken();
        return (int)in.nval;
    }
}