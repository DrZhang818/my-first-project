import java.util.*;
import java.io.*;

public class CinemaCashier {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        int mid = (k + 1) / 2;
        int[][] vis = new int[k + 1][k + 1];
        for(int t = 1; t <= n; t++) {
            int m = sc.nextInt();
            int mn = 1000000000, x = -1, yl = -1, yr = -1;
            for(int i = 1; i <= k; i++) {
                int dis = Math.abs(mid - i) * m;
                int c = 0;
                for(int l = 1, r = 1; r <= k; r++) {
                    dis += Math.abs(mid - r);
                    c += vis[i][r];
                    if(r < m) {
                        continue;
                    }
                    if(dis < mn && c == 0) {
                        mn = dis;
                        x = i;
                        yl = l;
                        yr = r;
                    }
                    dis -= Math.abs(mid - l);
                    c -= vis[i][l];
                    l++;
                }
            }
            if(x == -1) {
                out.println(-1);
                continue;
            }
            for(int j = yl; j <= yr; j++) {
                vis[x][j] = 1;
            }
            out.println(x + " " + yl + " " + yr);
        }

        out.flush();
    }

}