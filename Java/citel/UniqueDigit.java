import java.util.Scanner;

public class UniqueDigit {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int i = 0; i < T; i++) {
            String s = sc.next();
            boolean[] vis = new boolean[10];
            for(char c : s.toCharArray()) {
                if('0' <= c && c <= '9') {
                    if(vis[c - '0'] == false) {
                        vis[c - '0'] = true;
                        System.out.print(c);
                    }
                }
            }
            System.out.println();
        }
        sc.close();
    }
}