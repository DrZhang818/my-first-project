import java.util.Scanner;

public class DistanceBetweenPoints {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()) {
            String s = sc.nextLine();
            String t = sc.nextLine();
            int x = 1, y = 1;
            for(int i = 0; i < s.length(); i++) {
                int cur = s.charAt(i) - 'A' + 1;
                x = x * cur % 47;
            }
            for(int i = 0; i < t.length(); i++) {
                int cur = t.charAt(i) - 'A' + 1;
                y = y * cur % 47;
            }
            if(x == y) {
                System.out.println("GO");
            } else {
                System.out.println("STAY");
            }
        }
    }
}