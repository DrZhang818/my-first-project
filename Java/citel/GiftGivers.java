import java.io.*;
import java.util.*;

public class GiftGivers {
    static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
    
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    
    public static void main(String[] args) throws IOException {
        int n = nextInt();
        Map<String, Integer> mp = new LinkedHashMap<>();
        for(int i = 0; i < n; i++) {
            mp.put(nextString(), 0);
        } 
        for(int i = 0; i < n; i++) {
            String S = nextString();
            int tot = nextInt();
            int k = nextInt();
            if(k == 0) {
                continue;
            }    
            int x = tot / k;
            mp.put(S, mp.get(S) - k * x);
            for(int j = 0; j < k; j++) {
                String T = nextString();
                mp.put(T, mp.get(T) + x);
            }
        }
        for(Map.Entry<String,Integer> o : mp.entrySet()) {
            out.println(o.getKey() + " " + o.getValue());
        }
        out.flush();
    }    

    static int nextInt() throws IOException {
        in.nextToken();
        return (int)in.nval;
    }

    static String nextString() throws IOException {
        in.nextToken();
        return in.sval;
    }
}