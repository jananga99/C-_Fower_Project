#ifndef TEST2_ORDER_VALIDATION_H
#define TEST2_ORDER_VALIDATION_H

#include <string>
#include <unordered_set>

class OrderValidation
{
private:
    const std::unordered_set<std::string> validInstruments ={"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};

    // Validating clientOrderID.
    bool validateClientOrderID(std::string clientOrderID, std::string* rejectedReason){
        if(clientOrderID.length() > 20){
            *rejectedReason = "Client order ID is too long";
            return false;
        }
        return true;
    }

    // Validating instrument is one of the 5 valid instruments.
    bool validateIntrument(std::string instrument, std::string* rejectedReason){
        if(validInstruments.find(instrument) == validInstruments.end()){
            *rejectedReason = "Instrument is not valid";
            return false;
        }
        return true;
    }

    // Validating side is either 1 or 2.
    bool validateSide(int side, std::string* rejectedReason){
        if(side != 1 && side != 2){
            *rejectedReason = "Side is not valid";
            return false;
        }
        return true;
    }

    // Validating price larger than 0.
    bool validatePrice(double price, std::string* rejectedReason){
        if(price <= 0){
            *rejectedReason = "Price is not valid";
            return false;
        }
        return true;
    }

    // Validating quantity larger than 0 and less than 1000. Also this validates it a multiplication of 10.
    bool validateQuantity(int quantity, std::string* rejectedReason){
        if((quantity <= 0) || (quantity > 1000) || (quantity % 10 != 0)){
            *rejectedReason = "Quantity is not valid";
            return false;
        }
        return true;
    }

public:
    bool validateOrderFields(std::string clientOrderID, std::string instrument, int side, int quantity, double price, std::string* rejectedReason){
        return validateClientOrderID(clientOrderID, rejectedReason) && 
                validateIntrument(instrument, rejectedReason) && 
                validateSide(side, rejectedReason) && 
                validateQuantity(quantity, rejectedReason) && 
                validatePrice(price, rejectedReason);
    }
    
};




#endif
