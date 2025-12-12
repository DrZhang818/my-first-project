import java.util.Scanner;

public class PointPosition {
    public static void main(String[] args) {
        double x1, y1, x2, y2, x0, y0;
        Scanner sc = new Scanner(System.in);
        x0 = sc.nextDouble();
        y0 = sc.nextDouble();
        x1 = sc.nextDouble();
        y1 = sc.nextDouble();
        x2 = sc.nextDouble();
        y2 = sc.nextDouble();
        double eps = 1E-7;
        double res = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
        if(Math.abs(res) <= eps) {
            System.out.printf("(%.1f, %.1f) is on the line from (%.1f, %.1f) to (%.1f, %.1f)", x2, y2, x0, y0, x1, y1);
        } else if(res > 0) {
            System.out.printf("(%.1f, %.1f) is on the left side of the line from (%.1f, %.1f) to (%.1f, %.1f)", x2, y2, x0, y0, x1, y1);
        } else {
            System.out.printf("(%.1f, %.1f) is on the right side of the line from (%.1f, %.1f) to (%.1f, %.1f)", x2, y2, x0, y0, x1, y1);
        }
    }
}