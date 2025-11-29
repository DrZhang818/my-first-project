import java.util.*;

public class ValueAddedTax {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T;
        T = sc.nextInt();
        while(T-- > 0) {
            String s = sc.next();
            int cost = sc.nextInt();
            int n = sc.nextInt();
            HashSet<String> st = new HashSet<>();
            for(int i = 1; i <= n; i++) {
                String t = sc.next();
                st.add(t);
            }
            if(st.contains(s)) {
                System.out.printf("%.2f\n", cost * (1.1));
            } else {
                System.out.printf("%.2f\n", cost * (1.18));
            }
        }
    }
}