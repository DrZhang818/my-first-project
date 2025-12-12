import java.util.Scanner;

public class DistanceBetweenPoints {
    public static void main(String[] args) {
        int T;
        Scanner sc = new Scanner(System.in);
        T = sc.nextInt();
        while(T-- > 0) {
            double x1, y1, x2, y2;
            x1 = sc.nextDouble();
            y1 = sc.nextDouble();
            x2 = sc.nextDouble();
            y2 = sc.nextDouble();
            double ans = Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
            System.out.printf("%.4f\n", ans);
        }
    }
}