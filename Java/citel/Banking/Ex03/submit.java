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
    private SavingsAccount savingsAccount = null;
    private CheckingAccount checkingAccount = null; 

    public Customer(String f, String l) {
        this.firstName = f;
        this.lastName = l;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public SavingsAccount getSavings() {
        return savingsAccount;
    }

    public void setSavings(SavingsAccount s) {
        this.savingsAccount = s;
    }

    public CheckingAccount getChecking() {
        return checkingAccount;
    }

    public void setChecking(CheckingAccount c) {
        this.checkingAccount = c;
    }

    @Override
    public String toString() {
        return "[" + lastName + ", " + firstName + "]";
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
    private SavingsAccount protectedBy = null;

    public CheckingAccount(double balance) {
        super(balance);
    }

    public CheckingAccount(double balance, SavingsAccount protect) {
        super(balance);
        protectedBy = protect;
    }

    @Override
    public boolean withdraw(double amt) {
        if(balance >= amt) {
            balance -= amt;
            return true;
        }
        if(this.protectedBy == null) {
            return false;
        }
        double need = amt - balance;
        if(protectedBy.getBalance() >= need) {
            protectedBy.withdraw(need);
            balance = 0.0;
            return true;
        }
        return false;
    }
}