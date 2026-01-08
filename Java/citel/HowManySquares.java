import java.util.*;
import java.io.*;

public class HowManySquares {
    static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    static Scanner sc = new Scanner(System.in);

    public static void solve() throws IOException {
        int n = sc.nextInt();
        int m = sc.nextInt();
        char[][] grid = new char[n][m];
        for (int i = 0; i < n; i++) {
            grid[i] = sc.next().toCharArray();
        }
        boolean[][] visited = new boolean[n][m];
        int squareCount = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    List<Point> component = new ArrayList<>();
                    Queue<Point> q = new LinkedList<>();
                    Point start = new Point(i, j);
                    q.add(start);
                    visited[i][j] = true;
                    while (!q.isEmpty()) {
                        Point curr = q.poll();
                        component.add(curr);
                        for (int dr = -1; dr <= 1; dr++) {
                            for (int dc = -1; dc <= 1; dc++) {
                                if (dr == 0 && dc == 0) continue;
                                int nr = curr.r + dr;
                                int nc = curr.c + dc;
                                if (nr >= 0 && nr < n && nc >= 0 && nc < m && 
                                    grid[nr][nc] == '1' && !visited[nr][nc]) {
                                    visited[nr][nc] = true;
                                    q.add(new Point(nr, nc));
                                }
                            }
                        }
                    }
                    if (isValidSquare(component)) {
                        squareCount++;
                    }
                }
            }
        }
        out.println(squareCount);
    }

    private static boolean isValidSquare(List<Point> points) {
        if (points.size() < 4) return false;
        int minR = 300, maxR = -1, minC = 300, maxC = -1;
        for (Point p : points) {
            if (p.r < minR) minR = p.r;
            if (p.r > maxR) maxR = p.r;
            if (p.c < minC) minC = p.c;
            if (p.c > maxC) maxC = p.c;
        }
        int h = maxR - minR + 1;
        int w = maxC - minC + 1;
        if (h != w || h < 2) return false;
        boolean isType1 = true;
        if (points.size() != 4 * h - 4) {
            isType1 = false;
        } else {
            for (Point p : points) {
                if (!(p.r == minR || p.r == maxR || p.c == minC || p.c == maxC)) {
                    isType1 = false;
                    break;
                }
            }
        }
        if (isType1) return true;
        if (h % 2 == 0) return false;
        int k = (h + 1) / 2;
        if (points.size() != 4 * k - 4) return false;
        int midR = (minR + maxR) / 2;
        int midC = (minC + maxC) / 2;
        for (Point p : points) {
            if (Math.abs(p.r - midR) + Math.abs(p.c - midC) != k - 1) {
                return false;
            }
        }
        return true;
    }

    static class Point {
        int r, c;
        Point(int r, int c) { this.r = r; this.c = c; }
    }

    public static void main(String[] args) throws IOException {
        if (sc.hasNextInt()) {
            int t = sc.nextInt();
            while (t-- > 0) {
                solve();
            }
        }
        out.flush();
    }
}