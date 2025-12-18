import java.text.NumberFormat;
import java.util.*;
class CustomerReport {
    public void generateReport() {
        Bank bank = Bank.getBank();
        
        NumberFormat currency_format = NumberFormat.getCurrencyInstance(Locale.US);

        System.out.println("CUSTOMERS REPORT");
        System.out.println("================");

        for (int cust_idx = 0; cust_idx < bank.getNumOfCustomers(); cust_idx++) {
            Customer customer = bank.getCustomer(cust_idx);

            System.out.println();
            System.out.println("Customer: " + customer.getLastName() + ", " + customer.getFirstName());

            for (int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++) {
                Account account = customer.getAccount(acct_idx);
                String account_type = "";

                if (account instanceof SavingsAccount) {
                    account_type = "Savings Account";
                } else if (account instanceof CheckingAccount) {
                    account_type = "Checking Account";
                } else {
                    account_type = "Unknown Account Type";
                }

                System.out.println("    " + account_type + ": current balance is " + currency_format.format(account.getBalance()));
            }
        }
    }
}