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