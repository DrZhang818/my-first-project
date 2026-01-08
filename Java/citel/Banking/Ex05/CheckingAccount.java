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
                throw new OverdraftException("Insufficient funds", deficit - overdraftProtection);
            } else {
                overdraftProtection -= deficit;
                balance = 0;
            }
        }
    }
}