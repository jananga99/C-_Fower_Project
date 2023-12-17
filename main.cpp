#include <iostream>
#include "Order/Order.h"
#include "SortedLinkedList/SortedLinkedList.h"
#include "ExchangeApplication/ExchangeApplication.h"
#include "CSVManager/CSVManager.h"
#include "Transaction/Transaction.h"
#include <list>
#include "OrderBook/OrderBook.h"

int Order::count = 0;

int main() {

    ExchangeApplication app2 = *new ExchangeApplication();

    
    CSVManager csvmanager = *new CSVManager();
    std::string filename = "/home/malith/Documents/C-_Fower_Project/CSVFiles/orders.csv";
    std::list<Order> orders = csvmanager.readOrders(filename);

    // Adding the orders.
    for(auto& i : orders){
        std::string instrument = i.getInstrument();
        app2.addOrder(&i, instrument);
    }
    
    // Writing the csv file using the transactions.
    std::list <Transaction> transactions = OrderBook::getTransactions();
    std::string filename2 = "/home/malith/Documents/C-_Fower_Project/CSVFiles/transactions.csv";
    csvmanager.writeTransactions(filename2, transactions);

    return 0;
}
