import java.util.Scanner;

public class repeat3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = Integer.parseInt(sc.nextLine());
        for(int i = 0; i < T; i++) {
            String Line = sc.nextLine();
            int idx = Line.indexOf(' ');
            String num = Line.substring(0, idx);
            String s = Line.substring(idx + 1);
            int n = Integer.parseInt(num);
            for(int j = 0; j < n; j++) {
                System.out.print(s);
            }
            System.out.println();
        }
        sc.close();
    }
}