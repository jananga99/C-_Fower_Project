//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_ORDER_H
#define TEST2_ORDER_H


#include <string>
#include "OrderValidation.h"



class Order {
private:
    std::string clientOrderID;
    std::string instrument;
    int side;
    int quantity;
    double price;
    std::string orderID;
    OrderValidation orderValidation;
public:
    static int count;
    Order(std::string clientOrderID, std::string instrument, int side, int quantity, int price){
        if(orderValidation.validateOrderFields(clientOrderID, instrument, side, quantity, price)){
            this->clientOrderID = clientOrderID;
            this->instrument = instrument;
            this->side = side;
            this->quantity = quantity;
            this->price = price;

            orderID = "ord" + std::to_string(count+1);
            count ++;
            std::cout << "Order " << orderID << " created" << std::endl;
        }else{
                std::cout << "Invalid order. Client order ID: " << clientOrderID << std::endl;
        }
    }

    // Returns the order which should be on top of the order book
    static Order getMinOrder(Order order1, Order order2) {
        if(order1.price == order2.price){
            if (order1.orderID > order2.orderID) {
                return order2;
            } else {
                return order1;
            }
        }else{
            if (order1.side == 1) {
                if (order1.price > order2.price) {
                    return order1;
                } else {
                    return order2;
                }
            } else {
                if (order1.price < order2.price) {
                    return order1;
                } else  {
                    return order2;
                }
            }
        }
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    [[nodiscard]] int getSide() const {
        return side;
    }

    [[nodiscard]] std::string getOrderID() const {
        return orderID;
    }

    [[nodiscard]] int getQuantity() const {
        return quantity;
    }

    [[nodiscard]] double getPrice() const {
        return price;
    }

    [[nodiscard]] std::string getInstrument() const {
        return instrument;
    }

    [[nodiscard]] std::string getClientOrderID() const {
        return clientOrderID;
    }


    void print() {
        std::cout  << orderID << " " << clientOrderID << " " << instrument << " "<< side << " "<< quantity << " " << price << std::endl;
    }

};


#endif //TEST2_ORDER_H
