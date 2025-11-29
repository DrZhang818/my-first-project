import java.io.*;
import java.util.*;

public class jingsai {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StreamTokenizer in = new StreamTokenizer(br);
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

        in.nextToken();
        int n = (int)in.nval;
        Integer[] arr = new Integer[n];
        for(int i = 0; i < n; i++) {
            in.nextToken();
            arr[i] = (int)in.nval;
        }
        for(int i = 0; i < n; i++) {
            out.print(arr[i] + " ");
        }
        out.println();
        out.flush();
        out.close();
    }
}