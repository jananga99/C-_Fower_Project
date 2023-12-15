#include <iostream>
#include "Order/Order.h"
#include "SortedLinkedList/SortedLinkedList.h"
#include "ExchangeApplication/ExchangeApplication.h"

int Order::count = 0;

int main() {

    std::string instrument = "Rose";

    ExchangeApplication app2 = *new ExchangeApplication();
    const int numOrders2 = 3;
    Order  orders2[numOrders2] = {
            Order("aa13", "Rose", 3, 100, 55),
            Order("aa14", "Rose", 2, 100, 45),
            Order("aa15", "Rose", 1, 100, 35)
    };
    for(auto & i : orders2){
        app2.addOrder(&i, instrument);
    }
    (*app2.getOrderBook(instrument)).print();

//    ExchangeApplication app3 = *new ExchangeApplication();
//    const int numOrders3 = 3;
//    Order  orders3[numOrders3] = {
//            Order("aa13", "Rose", 2, 100, 55),
//            Order("aa14", "Rose", 2, 100, 45),
//            Order("aa15", "Rose", 1, 100, 45)
//    };
//    for(auto & i : orders3){
//        app3.addOrder(&i, instrument);
//    }
//    (*app3.getOrderBook(instrument)).print();

//    ExchangeApplication app4 = *new ExchangeApplication();
//    const int numOrders4 = 3;
//    Order  orders4[numOrders4] = {
//            Order("aa13", "Rose", 2, 100, 55),
//            Order("aa14", "Rose", 2, 100, 45),
//            Order("aa15", "Rose", 1, 200, 45)
//    };
//    for(auto & i : orders4){
//        app4.addOrder(&i, instrument);
//    }
//    (*app4.getOrderBook(instrument)).print();

//    ExchangeApplication app5 = *new ExchangeApplication();
//    const int numOrders5 = 3;
//    Order  orders5[numOrders5] = {
//            Order("aa13", "Rose", 1, 100, 55),
//            Order("aa14", "Rose", 1, 100, 65),
//            Order("aa15", "Rose", 2, 300, 1)
//    };
//    for(auto & i : orders5){
//        app5.addOrder(&i, instrument);
//        (*app5.getOrderBook(instrument)).print();
//    }



//    ExchangeApplication app6 = *new ExchangeApplication();
//    const int numOrders6 = 4;
//    Order  orders5[numOrders6] = {
//            Order("aa13", "Rose", 1, 100, 55),
//            Order("aa14", "Rose", 1, 100, 65),
//            Order("aa15", "Rose", 2, 300, 1),
//            Order("aa16", "Rose", 1, 100, 2)
//    };
//    for(auto & i : orders5){
//        app6.addOrder(&i, instrument);
//    }
//    (*app6.getOrderBook(instrument)).print();





//    OrderBook ob = *new OrderBook(instrument);
//    ob.addOrder(&orders[0]);
//    ob.addOrder(&orders[5]);
//    ob.print();






//    SortedLinkedList list = *new SortedLinkedList();
//
//    list.insert(&orders[1]);
//    list.insert(&orders[4]);
//    list.insert(&orders[3]);
//    list.insert(&orders[2]);
//    list.insert(&orders[0]);

//    Order max1 = Order::getMinOrder(orders[4], orders[0]);
//    max1.print();

//    list.print();
//
//    list.remove(&orders[2]);
//    list.remove(&orders[4]);
//
//    list.print();


    return 0;
}
