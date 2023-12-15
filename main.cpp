#include <iostream>
#include "Order/Order.h"
#include "SortedLinkedList/SortedLinkedList.h"
#include "ExchangeApplication/ExchangeApplication.h"
#include "CSVManager/CSVManager.h"

int Order::count = 0;

int main() {

    ExchangeApplication app2 = *new ExchangeApplication();

    
    CSVManager reader = *new CSVManager();
    std::string filename = "/home/malith/Documents/C-_Fower_Project/CSVFiles/orders.csv";
    std::list<Order> orders = reader.readOrders(filename);
  
    for(auto & i : orders){
        app2.addOrder(&i, instrument);
    }
    (*app2.getOrderBook(instrument)).print();


    return 0;
}
