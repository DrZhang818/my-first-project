import java.text.NumberFormat;
import java.util.*;
class Main {
  public static void main(String[] args) {
    Bank bank = Bank.getBank();
    Customer customer;
    int curCustomer = 0;
    Scanner s = new Scanner(System.in);
    int t = s.nextInt();
    s.nextLine();
    // Create several customers and their accounts according to data
    while (t-- > 0) {
      String f = s.next();
      String l = s.next();
      s.nextLine();
      bank.addCustomer(f, l);
      customer = bank.getCustomer(curCustomer++);
      int numAccount = s.nextInt();
      s.nextLine();
      while (numAccount-- > 0) {
        String[] type = s.nextLine().split(" ");
        double balance;
        double interesOrProtect;
        char op = type[0].charAt(0);
        if (op == 'C' || op == 'c') {
          balance = Double.parseDouble(type[1]);
          if (type.length == 3) {
            interesOrProtect = Double.parseDouble(type[2]);
            customer.addAccount(new CheckingAccount(balance,
                interesOrProtect));
          } else {
            customer.addAccount(new CheckingAccount(balance));
          }
        } else if (op == 'S' || op == 's') {
          balance = Double.parseDouble(type[1]);
          interesOrProtect = Double.parseDouble(type[2]);
          customer.addAccount(new SavingsAccount(balance,
              interesOrProtect));
        } else if (op == 'A' || op == 'a') {
          int cIndex = Integer.parseInt(type[1]);
          int aIndex = Integer.parseInt(type[2]);
          customer.addAccount(bank.getCustomer(cIndex).getAccount(
              aIndex));
        }
      }
    }
    
    CustomerReport cr = new CustomerReport();
    cr.generateReport();
  }
}