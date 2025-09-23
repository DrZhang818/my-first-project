import java.util.Scanner;

public class DigitCount {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int T = sc.nextInt();
        for(int i = 0; i < T; i++) {
            int n = sc.nextInt();
            int ans = 0;
            n = n >= 0 ? n : -n;
            do {
                ans += 1;
                n /= 10;
            } while(n > 0);
            System.out.println(ans);
        }

        sc.close();
    }
}