import java.util.*;
class Customer implements Comparable<Customer> {
    private String firstName;
    private String lastName;
    private List<Account> accounts;

    public Customer(String f, String l) {
        this.firstName = f;
        this.lastName = l;
        this.accounts = new ArrayList<>();
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

    public Iterator<Account> getAccounts() {
        return accounts.iterator();
    }

    @Override
    public int compareTo(Customer other) {
        int res = this.lastName.compareTo(other.lastName);
        if(res == 0) {
            res = this.firstName.compareTo(other.firstName);
        }
        return res;
    }

    @Override
    public String toString() {
        return "[" + firstName + " " + lastName + "]";
    }
}