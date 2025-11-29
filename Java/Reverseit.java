import java.util.Scanner;

public class Reverseit {
    static String norm(String s) {
        boolean neg = s.charAt(0) == '-';
        int i = 0;
        String res = "";
        if(neg) {
            i++;
            res += '-';
        }
        while(i < s.length() && s.charAt(i) == '0') {
            i++;
        }
        if(i == s.length()) {
            return "0";
        }
        while(i < s.length()) {
            res += s.charAt(i);
            i++;
        }
        return res;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        while (T-- > 0) {
            String s = sc.next();
            s = norm(s);
            int neg = s.charAt(0) == '-' ? 1 : 0;
            String res = "";
            if(neg == 1) res += '-';
            for(int i = s.length() - 1; i >= neg; i--) {
                res += s.charAt(i);
            }
            res = norm(res);
            System.out.println(res);
        }
    }
}