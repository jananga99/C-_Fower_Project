#ifndef TEST2_TRANSACTION_H
#define TEST2_TRANSACTION_H

#include <string>
#include <chrono>
#include <iomanip>

class Transaction{
private:
    std::string clientOrderID;
    std::string OrderID;
    std::string instrument;
    int side;
    double price;
    int quantity;
    int status;
    std::string rejectedReason;
    std::string timestamp;

    void setTimestamp(){
        // Get the current time point
        auto now = std::chrono::system_clock::now();

        // Convert the time point to a time_t object
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

        // Extract the components of the time
        std::tm timeInfo = {};
        localtime_r(&currentTime, &timeInfo);

        // Get the milliseconds
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        // Format the timestamp
        std::ostringstream oss;
        oss << std::put_time(&timeInfo, "%Y%m%d-%H%M%S.") << std::setw(3) << std::setfill('0') << milliseconds.count();

        this->timestamp = oss.str();
    }


public:
   Transaction(
        std::string clientOrderID,
        std::string OrderID,
        std::string instrument,
        int side,
        double price,
        int quantity,
        int status,
        std::string rejectedReason){
            this->clientOrderID = clientOrderID;
            this->OrderID = OrderID;
            this->instrument = instrument;
            this->side = side;
            this->price = price;
            this->quantity = quantity;
            this->status = status;
            this->rejectedReason = rejectedReason;
            setTimestamp();
   }

    std::string getClientOrderID(){
         return clientOrderID;
    }

    std::string getOrderID(){
         return OrderID;
    }

    std::string getInstrument(){
         return instrument;
    }

    int getSide(){
         return side;
    }

    double getPrice(){
         return price;
    }

    int getQuantity(){
         return quantity;
    }

    int getStatus(){
         return status;
    }

    std::string getRejectedReason(){
         return rejectedReason;
    }

    std::string getTimestamp(){
         return timestamp;
    }

};



#endif // TEST2_TRANSACTION_H