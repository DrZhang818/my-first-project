import java.util.Scanner;

public class BinaryForm {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t;
        t = sc.nextInt();
        while(t-- > 0) {
            int x;
            x = sc.nextInt();
            int[] a = new int[32];
            for(int i = 31; i >= 0; i--) {
                a[31 - i] = x >> i & 1;
            }
            int p = 0;
            while (p < 31 && a[p] == 0) {
                p++;
            }
            for(; p <= 31; p++) {
                System.out.print(a[p]);
            }
            System.out.println();
        }
    }
}