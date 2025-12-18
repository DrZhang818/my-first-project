class Bank {
    private static Bank bankInstance = new Bank();

    private List<Customer> customers;

    private Bank() {
        customers = new ArrayList<>();
    }

    public static Bank getBank() {
        return bankInstance;
    }

    public void addCustomer(String f, String l) {
        customers.add(new Customer(f, l));
    }

    public int getNumOfCustomers() {
        return customers.size();
    }

    public Customer getCustomer(int i) {
        return customers.get(i);
    }
}


class CustomerReport {
    public void generateReport() {
        Bank bank = Bank.getBank();
        
        NumberFormat currency_format = NumberFormat.getCurrencyInstance(Locale.US);

        System.out.println("CUSTOMERS REPORT");
        System.out.println("================");

        for (int cust_idx = 0; cust_idx < bank.getNumOfCustomers(); cust_idx++) {
            Customer customer = bank.getCustomer(cust_idx);

            System.out.println();
            System.out.println("Customer: " + customer.getLastName() + ", " + customer.getFirstName());

            for (int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++) {
                Account account = customer.getAccount(acct_idx);
                String account_type = "";

                if (account instanceof SavingsAccount) {
                    account_type = "Savings Account";
                } else if (account instanceof CheckingAccount) {
                    account_type = "Checking Account";
                } else {
                    account_type = "Unknown Account Type";
                }

                System.out.println("    " + account_type + ": current balance is " + currency_format.format(account.getBalance()));
            }
        }
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
    private double overdraftProtection = -1.0;

    public CheckingAccount(double balance) {
        super(balance);
    }

    public CheckingAccount(double balance, double protect) {
        super(balance);
        overdraftProtection = protect;
    }

    @Override
    public boolean withdraw(double amt) {
        if(balance >= amt) {
            balance -= amt;
            return true;
        }
        if(overdraftProtection >= 0 && overdraftProtection + balance >= amt) {
            overdraftProtection -= amt - balance;
            balance = 0;
            return true;
        }
        return false;
    }
}