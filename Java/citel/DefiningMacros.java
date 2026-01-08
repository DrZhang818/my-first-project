import java.util.*;

public class DefiningMacros {
    static Map<String, Integer> mp = new HashMap<>();

    static String norm(String s) {
        StringBuilder t = new StringBuilder();
        for(char c : s.toCharArray()) {
            if(c != ' ') {
                t.append(c);
            }
        }
        return t.toString();
    }

    static int dfs(String s) {
        if(s.isEmpty()) return 2;
        if(s.length() >= 2 && s.charAt(0) == '(' && s.charAt(s.length() - 1) == ')') {
            int cnt = 0;
            boolean ok = true;
            for(int i = 0; i < s.length() - 1; i++) {
                if(s.charAt(i) == '(') cnt++;
                if(s.charAt(i) == ')') cnt--;
                if(cnt == 0) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                int res = dfs(s.substring(1, s.length() - 1));
                return res == -1 ? -1 : 2;
            }
        }
        int cnt = 0, p1 = -1, p2 = -1;
        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == '(') {
                cnt++;
            } else if(s.charAt(i) == ')') {
                cnt--;
            } else if(cnt == 0) {
                if(s.charAt(i) == '+' || s.charAt(i) == '-') p1 = i;
                if(s.charAt(i) == '*' || s.charAt(i) == '/') p2 = i;
            }
        }
        if(p1 != -1) {
            int l = dfs(s.substring(0, p1));
            int r = dfs(s.substring(p1 + 1));
            if(l == -1 || r == -1) return -1;
            if(s.charAt(p1) == '-' && r == 0) return -1;
            return 0;
        }
        if(p2 != -1) {
            int l = dfs(s.substring(0, p2));
            int r = dfs(s.substring(p2 + 1));
            if(l <= 0 || r <= 0) return -1;
            if(s.charAt(p2) == '/' && r == 1) return -1;
            return 1;
        }
        return mp.containsKey(s) ? mp.get(s) : 2;
    }

    public static void solve() {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        for(int i = 1; i <= n; i++) {
            String line = sc.nextLine();
            String[] partsArray = line.trim().split("\\s+");
            List<String> parts = new ArrayList<>();
            for(String p : partsArray) {
                if(!p.isEmpty()) {
                    parts.add(p);
                }
            }
            int k = 0;
            while(!parts.get(k).equals("define") && !parts.get(k).equals("#define")) {
                k++;
            }
            String name = parts.get(k + 1);
            String expr = "";
            for(int j = k + 2; j < parts.size(); j++) {
                expr += parts.get(j);
            }
            mp.put(name, dfs(expr));
        }
        String line = sc.nextLine();
        if(dfs(norm(line)) == -1) {
            System.out.println("Suspicious");
        } else {
            System.out.println("OK");
        }
    }

    public static void main(String[] args) {
        solve();
    }
}