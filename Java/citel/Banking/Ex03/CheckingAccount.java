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