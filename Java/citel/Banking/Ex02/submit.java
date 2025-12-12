import java.util.*;
import java.text.NumberFormat;

public class Main {

    public static void main(String[] args) {
        Bank bank = new Bank();
        NumberFormat currency_format = NumberFormat.getCurrencyInstance(Locale.US);

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
                // Note: String comparison should use .equals(), not ==
                if (type[0].equalsIgnoreCase("C")) {
                    balance = Double.parseDouble(type[1]);
                    if (type.length == 3) {
                        interesOrProtect = Double.parseDouble(type[2]);
                        customer.addAccount(new CheckingAccount(balance, interesOrProtect));
                    } else {
                        customer.addAccount(new CheckingAccount(balance));
                    }
                } else if (type[0].equalsIgnoreCase("S")) {
                    balance = Double.parseDouble(type[1]);
                    interesOrProtect = Double.parseDouble(type[2]);
                    customer.addAccount(new SavingsAccount(balance, interesOrProtect));
                } else if (type[0].equalsIgnoreCase("A")) {
                    int cIndex = Integer.parseInt(type[1]);
                    int aIndex = Integer.parseInt(type[2]); // Assuming second param is aIndex
                    customer.addAccount(bank.getCustomer(cIndex).getAccount(aIndex));
                }
            }
        }

        // Generate a report
        System.out.println("CUSTOMERS REPORT");
        System.out.println("================");

        for ( int cust_idx = 0; cust_idx < bank.getNumOfCustomers(); cust_idx++ ) {
            customer = bank.getCustomer(cust_idx);

            System.out.println();
            System.out.println("Customer: "
                    + customer.getLastName() + ", "
                    + customer.getFirstName());

            for ( int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++ ) {
                Account account = customer.getAccount(acct_idx);
                String account_type = "";

                // Determine the account type
                if (account instanceof SavingsAccount) {
                    account_type = "Savings Account";
                } else if (account instanceof CheckingAccount) {
                    account_type = "Checking Account";
                }


                // Print the current balance of the account
                System.out.println("    " + account_type + currency_format.format(account.getBalance()));

            }
        }
    }
}


class Bank {
    private java.util.List<Customer> customers;

    public Bank() {
        customers = new java.util.ArrayList<>();
    }

    public void addCustomer(String f, String l) {
        customers.add(new Customer(f, l));
    }

    public int getNumOfCustomers() {
        return customers.size();
    }

    public Customer getCustomer(int i) {
        return customers.get(i) ;
    }
}

class Customer {
    private String firstName;
    private String lastName;
    private List<Account> accounts;

    public Customer(String f, String l) {
        this.firstName = f;
        this.lastName = l;
        accounts = new ArrayList<>();
    }

    public String getFirstName() {
        return this.firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public void addAccount(Account x) {
        accounts.add(x);
    }

    public Account getAccount(int i) {
        return accounts.get(i);
    }

    public int getNumOfAccounts() {
        return accounts.size();
    }
}


class Account {
    protected double balance;

    public Account(double init_balance) {
        this.balance = init_balance;
    }

    public double getBalance() {
        return balance;
    }

    public boolean deposit(double amt) {
        balance += amt;
        return true;
    }

    public boolean withdraw(double amt) {
        if(amt <= balance) {
            balance -= amt;
            return true;
        }
        return false;
    }
}

class SavingsAccount extends Account {
    private double interestRate;

    public SavingsAccount(double balance, double interest_rate) {
        super(balance);
        this.interestRate = interest_rate;
    }
}

class CheckingAccount extends Account {
    private double overdraftProtection;

    public CheckingAccount(double balance) {
        super(balance);
        this.overdraftProtection = -1.0;
    }

    public CheckingAccount(double balance, double protect) {
        super(balance);
        this.overdraftProtection = protect;
    }

    @Override
    public boolean withdraw(double amt) {
        if(balance >= amt) {
            balance -= amt;
            return true;
        }
        if(overdraftProtection == -1.0) {
            return false;
        }
        double need = amt - balance;
        if(overdraftProtection >= need) {
            balance = 0;
            overdraftProtection -= need;
            return true;
        }
        return false;
    }
}