/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */
import java.util.Scanner;
class Main {
  public static void main(String[] args) {
    Bank bank = new Bank();
    Customer customer;
      Account account;
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
        boolean protectWithSavings;
        char op = type[0].charAt(0);
        if (op == 'C' || op == 'c') {
          balance = Double.parseDouble(type[1]);
          protectWithSavings = Boolean.parseBoolean(type[2]);
          if (protectWithSavings) {
            customer.setChecking(new CheckingAccount(balance,
                customer.getSavings()));
            System.out.println(customer + " create Checking account: " + customer.getChecking().getBalance() + " with a protecting savings accout: " + customer.getSavings().getBalance() );
          } else {
            customer.setChecking(new CheckingAccount(balance));
            System.out.println(customer + " create Checking account: " + customer.getChecking().getBalance() + " without protecting savings accout.");
          }
        } else if (op == 'S' || op == 's') {
          balance = Double.parseDouble(type[1]);
          double interestRate = Double.parseDouble(type[2]);
          customer.setSavings(new SavingsAccount(balance,
              interestRate));
          System.out.println(customer + " create savings account: " + customer.getSavings().getBalance() );
        }
      }
    }
    int nOPs = s.nextInt();
    s.nextLine();
    while (nOPs-- > 0) {
      String[] sOP = s.nextLine().split(" ");
      char op = sOP[0].charAt(0);
      int customerIndex = Integer.parseInt(sOP[1]);
      double amount = Double.parseDouble(sOP[2]);
      boolean result;
      switch(op){
      case 'w':
      case 'W':
        customer = bank.getCustomer(customerIndex);
        result = customer.getChecking().withdraw(amount);
        System.out.println("Checking acct " + customer + "withdraw " + amount + " succeeds? " + result);
        break;
      case 'd':
      case 'D':
        customer = bank.getCustomer(customerIndex);
        result = customer.getChecking().deposit(amount);
        System.out.println("Checking acct " + customer + "deposit " + amount + " succeeds? " + result);
        break;
      }       
    }   
    // Generate a report
    for (int cust_idx = 0; cust_idx < bank.getNumOfCustomers(); cust_idx++) {
      customer = bank.getCustomer(cust_idx);
      System.out.println();
      System.out.println("Customer: " + customer.getLastName() + ", "
          + customer.getFirstName());
      account = customer.getChecking();
        System.out.println("    has a checking balance of " + account.getBalance());
      account = customer.getSavings();
      if (account != null)
        System.out.println("    has a savings balance of " + account.getBalance());
    }
  }
}
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */