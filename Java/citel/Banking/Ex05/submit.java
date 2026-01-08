/* --- 这里是你的代码，修改了 CustomerReport 和 Customer 部分 --- */

class OverdraftException extends Exception {
    private double deficit;

    public OverdraftException(String message, double deficit) {
        super(message);
        this.deficit = deficit;
    }

    public double getDeficit() {
        return deficit;
    }
}

class NameComp implements Comparator<Customer> {
    @Override
    public int compare(Customer c1, Customer c2) {
        int res = c1.getLastName().compareTo(c2.getLastName());
        if (res == 0) {
            res = c1.getFirstName().compareTo(c2.getFirstName());
        }
        return res;
    }
}

class SavingComp implements Comparator<Customer> {
    @Override
    public int compare(Customer c1, Customer c2) {
        double b1 = 0, b2 = 0;
        for (int i = 0; i < c1.getNumOfAccounts(); i++) {
            if (c1.getAccount(i) instanceof SavingsAccount) b1 = c1.getAccount(i).getBalance();
        }
        for (int i = 0; i < c2.getNumOfAccounts(); i++) {
            if (c2.getAccount(i) instanceof SavingsAccount) b2 = c2.getAccount(i).getBalance();
        }
        return Double.compare(b1, b2);
    }
}

class Account {
    protected double balance;

    public Account(double initBalance) {
        this.balance = initBalance;
    }

    public double getBalance() {
        return balance;
    }

    public void deposit(double amt) {
        balance += amt;
    }

    public void withdraw(double amt) throws OverdraftException {
        if(amt > balance) {
            throw new OverdraftException("Insufficient funds", amt - balance);
        }
        balance -= amt;
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
        this.overdraftProtection = protect;
    }

    @Override
    public void withdraw(double amt) throws OverdraftException {
        if(balance >= amt) {
            balance -= amt;
        } else {
            double deficit = amt - balance;
            if(overdraftProtection <= 0) {
                throw new OverdraftException("No overdraft protection", deficit);
            } else if(overdraftProtection < deficit) {
                // 关键点：返回 缺口 - 保护额
                throw new OverdraftException("Insufficient funds", deficit - overdraftProtection);
            } else {
                overdraftProtection -= deficit;
                balance = 0;
            }
        }
    }
}

class Bank {
    private static Bank bankInstance = new Bank();
    private List<Customer> customers = new ArrayList<>();

    private Bank() {}

    public static Bank getBank() { return bankInstance; }
    
    public void addCustomer(String f, String l) {
        customers.add(new Customer(f, l));
    }

    public int getNumOfCustomers() { return customers.size(); }
    public Customer getCustomer(int i) { return customers.get(i); }
    public Iterator<Customer> getCustomers() { return customers.iterator(); }

    public void sortCustomers(Comparator<Customer> comparator) {
        Collections.sort(customers, comparator);
    }
}

class Customer {
    private String firstName;
    private String lastName;
    private List<Account> accounts;

    public Customer(String f, String l) {
        this.firstName = f;
        this.lastName = l;
        this.accounts = new ArrayList<>();
    }

    public String getFirstName() { return firstName; }
    public String getLastName() { return lastName; }

    public void addAccount(Account x) { accounts.add(x); }
    public Account getAccount(int i) { return accounts.get(i); }
    public int getNumOfAccounts() { return accounts.size(); }
    public Iterator<Account> getAccounts() { return accounts.iterator(); }

    // 删除了 compareTo 方法，因为它不再需要且会导致编译错误

    @Override
    public String toString() {
        return "[" + firstName + " " + lastName + "]";
    }
}

class CustomerReport {
    // 将参数去掉，以匹配预设 Main 里的 cr.generateReport()
    public void generateReport() {
        Bank bank = Bank.getBank();

        // 默认按姓名排序
        bank.sortCustomers(new NameComp());

        System.out.println("CUSTOMERS REPORT");
        System.out.println("================");

        Iterator<Customer> custs = bank.getCustomers();
        while (custs.hasNext()) {
            Customer customer = custs.next();
            System.out.println(); // 打印空行
            System.out.println("Customer: " + customer.toString());

            Iterator<Account> accts = customer.getAccounts();
            while (accts.hasNext()) {
                Account account = accts.next();
                String type = (account instanceof SavingsAccount) ? "Savings Account" : "Checking Account";
                System.out.println("    " + type + ": current balance is $" + account.getBalance());
            }
        }
    }
}