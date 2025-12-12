import java.util.Scanner;

public class DistanceBetweenPoints {
    public static void main(String[] args) {
        int T;
        Scanner sc = new Scanner(System.in);
        T = sc.nextInt();
        while(T-- > 0) {
            double x;
            x = sc.nextDouble();
            double ans = 5 * (x - 32) / 9;
            System.out.printf("%.2f\n", ans);
        }
    }
}