import java.util.Scanner;
public class StringLength {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = Integer.parseInt(sc.nextLine());
        for(int i = 0; i < t; i++) {
            String s = sc.nextLine();
            System.out.println(s.length());
        }
    }
}