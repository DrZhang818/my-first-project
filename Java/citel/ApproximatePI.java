import java.util.Scanner;

public class ApproximatePI {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        double sum = 0;
        for(int i = 1, s = 0; i <= n; i += 2, s ^= 1) {
            if(s % 2 == 0) {
                sum += 1.0 / i;
            } else {
                sum -= 1.0 / i;
            }
        }
        double PI = 4 * sum;
        System.out.printf("%.6f\n", PI);
        sc.close();
    }
}