/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */
import java.text.NumberFormat;
import java.util.*;
public class Main {
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
        if (type[0].trim().toUpperCase().equals("C")) {
          balance = Double.parseDouble(type[1]);
          if (type.length == 3) {
            interesOrProtect = Double.parseDouble(type[2]);
            customer.addAccount(new CheckingAccount(balance,
                interesOrProtect));
          } else {
            customer.addAccount(new CheckingAccount(balance));
          }
        } else if (type[0].trim().toUpperCase().equals("S")) {
          balance = Double.parseDouble(type[1]);
          interesOrProtect = Double.parseDouble(type[2]);
          customer.addAccount(new SavingsAccount(balance,
              interesOrProtect));
        }
      }
    }
    int nOPs = s.nextInt();
    s.nextLine();
    while (nOPs-- > 0) {
      String[] sOP = s.nextLine().split(" ");
      char op = sOP[0].charAt(0);
      int customerIndex = Integer.parseInt(sOP[1]);
      int accountIndex = Integer.parseInt(sOP[2]);
      double amount = Double.parseDouble(sOP[3]);
      switch (op) {
      case 'w':
      case 'W':
        customer = bank.getCustomer(customerIndex);
        try{
          customer.getAccount(accountIndex).withdraw(amount);
        }
        catch (OverdraftException ode){
          System.out.println( customer + " withdraw " + amount + ", " + ode.getMessage() + ": " + ode.getDeficit());
        }
        break;
      case 'd':
      case 'D':
        customer = bank.getCustomer(customerIndex);
        customer.getAccount(accountIndex).deposit(amount);
        break;
      }
    }
    // Generate a report
    CustomerReport cr = new CustomerReport();
    cr.generateReport();
  }
}
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */