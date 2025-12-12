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