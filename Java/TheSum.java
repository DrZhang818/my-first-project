import java.util.Scanner;

public class DistanceBetweenPoints {
    public static void main(String[] args) {
        int T;
        Scanner sc = new Scanner(System.in);
        T = sc.nextInt();
        for(int i = 1; i <= T; i++) {
            System.out.printf("Case %d: ", i);
            long x, y;
            x = sc.nextLong();
            y = sc.nextLong();
            if(x > y) {
                System.out.println();
            } else {
                long ans = 0;
                for(long i = x; i <= y; i++) {
                    ans += i;
                }
                SU
            }

        }
    }
}