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