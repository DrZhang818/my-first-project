import  java.util.Scanner;
public class SumOfDigits {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for(int i = 0; i < T; i++) {
            int n = sc.nextInt();
            n = n < 0 ? -n : n;
            int sum = 0;
            while(n > 0) {
                sum += n % 10;
                n /= 10;
            }
            System.out.println(sum);
        }
    }
}