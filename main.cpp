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


    for(int j= 0;j < 7; j++){
        ExchangeApplication app = *new ExchangeApplication();
        CSVManager csvManager = *new CSVManager();
        std::string fileNamePrefix = "./CSVFiles/ex"+std::to_string(j + 1);

        std::string filename = fileNamePrefix+"/orders.csv";
        printf("FIlename : %s\n", filename.c_str());
        std::list<Order> orders = csvManager.readOrders(filename);
        for(auto& i : orders){
            std::string instrument = i.getInstrument();
            app.addOrder(&i, instrument);
        }
        std::list <Transaction> transactions = OrderBook::getTransactions();
        std::string filename2 = fileNamePrefix+"/transactions.csv";
        csvManager.writeTransactions(filename2, transactions);
        OrderBook::clearTransactions();
        Order::resetCount();
    }



    return 0;
}
