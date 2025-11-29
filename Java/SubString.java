import java.util.Scanner;

public class SubString {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = Integer.parseInt(sc.nextLine());
        while(t-- > 0) {
            String Line = sc.nextLine();
            String[] token = Line.split(" ", 3);
            int L = Integer.parseInt(token[0]);
            int R = Integer.parseInt(token[1]);
            String s = token[2];
            if(L > R || L >= s.length()) {
                System.out.println("-1");
                continue;
            }
            String sub;
            if(R >= s.length()) {
                sub = s.substring(L);
            } else {
                sub = s.substring(L, R + 1);
            }
            System.out.println(sub);
        }
    }
}