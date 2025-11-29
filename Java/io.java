import java.io.*;
import java.util.*;

public class io {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StreamTokenizer in = new StreamTokenizer(br);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        in.nextToken();
        int n = (int)in.nval;
        int a[] = new int[n + 1];
        for(int i = 1; i <= n; i++) {
            in.nextToken();
            a[i] = (int)in.nval;
        }
        Arrays.sort(a, (p, q) -> p - q);
        int sum = 0;
        for(int i = 1; i <= n; i++) {
            out.print(a[i] + " ");
            sum += a[i];
        }
        out.println();
        out.println(sum);
        out.flush();
        out.close();
    }
}