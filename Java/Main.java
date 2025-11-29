import banking.*;

public class Main {
    public static void main(String[] args) {
        Bank bank = new Bank();

        bank.addCustomer("Enqi", "Zhang");
        bank.addCustomer("San", "Zhang");
        bank.addCustomer("EQ","Z");

        for(int i = 0; i < bank.getNumOfCustomers(); i++) {
            Customer customer = bank.getCustomer(i);
            System.out.println("Customer [" + (i + 1) + "] is "
                    + customer.getLastName() + ", "
                    + customer.getFirstName());
        }
    }
}