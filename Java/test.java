import java.util.Scanner;

public class test {
    public static void main(String[] args) {
        double a = 2.0;
        double b = 2.0;
        if(Math.abs(a / b - int(a / b + 0.5)) < 1E-7) {
            System.out.println(int(a / b + 0.5));
        }
        System.out.println(a / b);
    }
}