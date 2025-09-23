import java.util.Scanner;

public class repeat1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        sc.nextLine();
        String s;
        s = sc.nextLine();
        for(int i = 0; i < n; i++) {
            System.out.print(s);
        }
        sc.close();
    }
}