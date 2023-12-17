//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_ORDERBOOK_H
#define TEST2_ORDERBOOK_H


#include <iostream>
#include "../Order/Order.h"
#include "../SortedLinkedList/SortedLinkedList.h"
#include <list>
#include "../Transaction/Transaction.h"
#include "../CSVManager/CSVManager.h"

class OrderBook {
private:
    SortedLinkedList sellOrders;
    SortedLinkedList buyOrders;
    int numSellOrders;
    int numBuyOrders;
    std::string instrument;
    static inline std::list<Transaction> transactions;

    void addTransaction(Order* order, int quantity, int status){
        Transaction transaction(order->getClientOrderID(),
                                order->getOrderID(),
                                order->getInstrument(),
                                order->getSide(), 
                                order->getPrice(), 
                                quantity,
                                status,
                                order->getRejectedReason());
        transactions.push_back(transaction);
    }

public:
    explicit OrderBook(std::string instrument) : instrument(std::move(instrument)) {
        sellOrders = SortedLinkedList();
        buyOrders = SortedLinkedList();
        numSellOrders = 0;
        numBuyOrders = 0;
    }

    OrderBook() = default;

    // only if return True, insert new node to order book
    bool removeFillOrders(SortedLinkedList* orders, int* numOrders, Order* newOrder) {
        while ( *numOrders > 0) {
            Order *currentOrder = orders->getHead()->order;
            if (newOrder->getQuantity() > currentOrder->getQuantity()) {
                newOrder->setQuantity(newOrder->getQuantity() - currentOrder->getQuantity());
                orders->remove(currentOrder);
                (*numOrders)--;
                //TODO 2: Add PFill transaction to report for newOrder
                addTransaction(newOrder, currentOrder->getQuantity(), Status::Pfill);

                //TODO 3 : Add Fill transaction to report for currentOrder
                addTransaction(currentOrder, currentOrder->getQuantity(), Status::Fill);

            } else if (newOrder->getQuantity() < currentOrder->getQuantity()) {
                currentOrder->setQuantity(currentOrder->getQuantity() - newOrder->getQuantity());
                //TODO 4: Add Fill transaction to report for newOrder
                addTransaction(newOrder, newOrder->getQuantity(), Status::Fill);

                //TODO 5 : Add PFill transaction to report for currentOrder
                addTransaction(currentOrder, newOrder->getQuantity(), Status::Pfill);

                return false;
            } else {
                orders->remove(currentOrder);
                (*numOrders)--;
                //TODO 6: Add Fill transaction to report for newOrder
                addTransaction(newOrder, newOrder->getQuantity(), Status::Fill);

                //TODO 7 : Add Fill transaction to report for currentOrder
                addTransaction(currentOrder, currentOrder->getQuantity(), Status::Fill);

                return false;
            }
        }
        return true;
    }

    void addOrder(Order* newOrder){
        SortedLinkedList* currentOrders  = nullptr;
        SortedLinkedList* opposedOrders  = nullptr;
        int* currentCount = nullptr;
        int* opposedCount = nullptr;
        if(newOrder->getSide()==1){
            currentOrders = &buyOrders;
            opposedOrders = &sellOrders;
            currentCount = &numBuyOrders;
            opposedCount = &numSellOrders;
        }else{
            currentOrders = &sellOrders;
            opposedOrders = &buyOrders;
            currentCount = &numSellOrders;
            opposedCount = &numBuyOrders;
        }

        if(newOrder->getValidity()){
            if(removeFillOrders(opposedOrders, opposedCount, newOrder)){
                currentOrders->insert(newOrder);
                (*currentCount)++;
                // TODO 1 : Add new order add transaction to the execution report
                addTransaction(newOrder, newOrder->getQuantity(), Status::New);
            }
        
        }else{
                // TODO 8 : Add new order reject transaction to the execution report    
                addTransaction(newOrder, newOrder->getQuantity(), Status::Rejected);
            }
    }

    [[nodiscard]] SortedLinkedList getSellOrders() const {
        return sellOrders;
    }

    [[nodiscard]] SortedLinkedList getBuyOrders() const {
        return buyOrders;
    }

    [[nodiscard]] int getNumSellOrders() const {
        return numSellOrders;
    }

    [[nodiscard]] int getNumBuyOrders() const {
        return numBuyOrders;
    }

    [[nodiscard]] std::string getInstrument() const {
        return instrument;
    }

    void print() {
        std::cout << "=====================================" <<  std::endl;
        std::cout << "Order book for " << instrument << std::endl;
        std::cout << "Buy orders:" << std::endl;
        buyOrders.print();
        std::cout << "Sell orders:" << std::endl;
        sellOrders.print();
        std::cout << "=====================================" <<  std::endl;
    }

    void printTransactions(){
        std::cout << "=====================================" <<  std::endl
                    << "Transactions for " << instrument << std::endl;
                    
        for(auto & i : transactions){
            i.print();
        }
        std::cout << "=====================================" <<  std::endl;
    }

    static std::list<Transaction> getTransactions(){
        return transactions;
    }
};


#endif //TEST2_ORDERBOOK_H
