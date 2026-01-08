import java.util.*;

class CustomerReport {
    public void generateReport() {
        Bank bank = Bank.getBank();
        bank.sortCustomers();

        System.out.println("CUSTOMERS REPORT");
        System.out.println("================");

        Iterator<Customer> customers = bank.getCustomers();

        while(customers.hasNext()) {
            Customer customer = customers.next();
            
            System.out.println();
            System.out.println("Customer: " + customer.toString());

            Iterator<Account> accounts = customer.getAccounts();
            while(accounts.hasNext()) {
                Account account = accounts.next();
                String account_type = (account instanceof SavingsAccount) ? "Savings Account" : "Checking Account";
                System.out.println("    " + account_type + ": current balance is $" + account.getBalance());
            }
        }
    }
}