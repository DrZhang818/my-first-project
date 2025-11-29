package banking;

public class Bank {
    private Customer[] customers;
    private int numberOfCustomers;

    public Bank() {
        this.customers = new Customer[20];
        this.numberOfCustomers = 0;
    }

    public void addCustomer(String f, String l) {
        int i = this.numberOfCustomers++;
        this.customers[i] = new Customer(f, l);
    }

    public int getNumOfCustomers() {
        return this.numberOfCustomers;
    }

    public Customer getCustomer(int i) {
        return this.customers[i];
    }
}
