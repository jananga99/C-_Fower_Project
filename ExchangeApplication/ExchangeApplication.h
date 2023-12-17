//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_EXCHANGEAPPLICATION_H
#define TEST2_EXCHANGEAPPLICATION_H


#include "../OrderBook/OrderBook.h"

class ExchangeApplication {
private:
    OrderBook orderBooks[5];
    std::string instruments[5] = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
    int numOrderBooks;
public:
    ExchangeApplication() : numOrderBooks(5) {
        for (int i = 0; i < 5; i++){
            orderBooks[i] =*new OrderBook(instruments[i]);
        }
    }

    OrderBook* getOrderBook(std::string& instrument){
        OrderBook* currentOrderBook ;
        for (int i = 0; i < numOrderBooks; i++) {
            if (orderBooks[i].getInstrument() == instrument) {
                currentOrderBook = &orderBooks[i];
                break;
            }
        }
        return currentOrderBook;
    }
    
    void addOrder(Order* newOrder,  std::string& instrument) {
        OrderBook* orderBook = getOrderBook(instrument);
        (*orderBook).addOrder(newOrder);
    }
};


#endif //TEST2_EXCHANGEAPPLICATION_H
