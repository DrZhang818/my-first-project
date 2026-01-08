import java.util.*;
public class Bank {
    private static Bank bankInstance = new Bank();

    private List<Customer> customers;

    private Bank() {
        customers = new ArrayList<>();
    }

    public static Bank getBank() {
        return bankInstance;
    }

    public void addCustomer(String f, String l) {
        customers.add(new Customer(f, l));
    }

    public int getNumOfCustomers() {
        return customers.size();
    }

    public Customer getCustomer(int i) {
        return customers.get(i);
    }

    public void sortCustomers() {
        Collections.sort(customers);
    }

    public Iterator<Customer> getCustomers() {
        return customers.iterator();
    }
}
