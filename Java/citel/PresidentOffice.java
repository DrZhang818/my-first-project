import java.io.*;
import java.util.*;

class PresidentOffice {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));

    public static void solve() throws IOException {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();
        char c = sc.next().charAt(0);

        char[][] a = new char[n + 1][m + 1];
        for(int i = 1; i <= n; i++) {
            String s = sc.next();
            for(int j = 1; j <= m; j++) {
                a[i][j] = s.charAt(j - 1);
            }
        }

        int dir[] = {-1, 0, 1, 0, -1};

        Set<Character> st = new HashSet<>();
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(a[i][j] != c) {
                    continue;
                }
                for(int s = 0; s < 4; s++) {
                    int nx = i + dir[s], ny = j + dir[s + 1];
                    if(nx < 1 || nx > n || ny < 1 || ny > m) {
                        continue;
                    }
                    if(a[nx][ny] != c && a[nx][ny] != '.') {
                        st.add(a[nx][ny]);
                    }
                }
            }
        }

        out.println(st.size());
    }

    public static void main(String[] args) throws IOException {
        solve();
        out.flush();
    }
}