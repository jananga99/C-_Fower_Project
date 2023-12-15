#ifndef TEST2_ORDER_VALIDATION_H
#define TEST2_ORDER_VALIDATION_H

#include <string>
#include <unordered_set>

class OrderValidation
{
private:
    const std::unordered_set<std::string> validInstruments ={"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};

    // Validating clientOrderID.
    bool validateClientOrderID(std::string clientOrderID){
        return clientOrderID.length() <= 7;
    }

    // Validating instrument is one of the 5 valid instruments.
    bool validateIntrument(std::string instrument){
        return validInstruments.find(instrument) != validInstruments.end();
    }

    // Validating side is either 1 or 2.
    bool validateSide(int side){
        return side == 1 || side == 2;
    }

    // Validating price larger than 0.
    bool validatePrice(double price){
        return price > 0;
    }

    // Validating quantity larger than 0 and less than 1000. Also this validates it a multiplication of 10.
    bool validateQuantity(int quantity) {
    return (quantity > 0) && (quantity <= 1000) && (quantity % 10 == 0);
}
public:
    bool validateOrderFields(std::string clientOrderID, std::string instrument, int side, int quantity, double price){
        return validateClientOrderID(clientOrderID) && validateIntrument(instrument) && validateSide(side) && validateQuantity(quantity) && validatePrice(price);
    }
    
};




#endif