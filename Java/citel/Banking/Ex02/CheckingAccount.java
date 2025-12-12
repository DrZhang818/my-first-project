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