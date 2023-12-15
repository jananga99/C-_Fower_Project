#include <iostream>
#include "Order/Order.h"
#include "SortedLinkedList/SortedLinkedList.h"
#include "ExchangeApplication/ExchangeApplication.h"
#include "CSVReader/CSVReader.h"

int Order::count = 0;

int main() {

    ExchangeApplication app2 = *new ExchangeApplication();
    
    CSVReader reader = *new CSVReader();
    std::string filename = "/home/malith/Documents/C-_Fower_Project/CSVFiles/orders.csv";
    std::list<Order> orders = reader.readOrders(filename);


    return 0;
}
