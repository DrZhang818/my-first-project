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