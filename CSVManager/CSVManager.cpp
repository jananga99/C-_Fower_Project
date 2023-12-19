#include "CSVManager.h"

std::vector<std::string> enumValueArray = {"New", "Reject", "Fill", "PFill", };
std::list<Order> CSVManager::readOrders(const std::string& filename){

    std::list<Order> orders;
    
    std::ifstream file(filename);

    // Checking the availability of the file.
    if(!file.is_open()){
        std::cout << "CSV File not found" << std::endl;
        return orders;
    }

    std::string line;
    bool isHeader = true;
    while (std::getline(file, line)) {
        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        Order order(row[0], row[1], std::stoi(row[2]), std::stoi(row[3]), std::stod(row[4]));
        order.print();
        if (order.getValidity()){
            orders.push_back(order);
        }
        
    }

    file.close();
    return orders;
};

void CSVManager::writeTransactions(const std::string& filename, std::list<Transaction> transactions){
    std::ofstream file(filename);

    // Checking the availability of the file.
    if(!file.is_open()){
        std::cout << "CSV File not found" << std::endl;
        return;
    }

//    file << "ClientOrderID,OrderID,Instrument,Side,Price,Quantity,Status,RejectedReason,Timestamp" << std::endl;
    file << "OrderID,Cl. Ord. ID,Instrument,Side,Exec Status,Quantity,Price,Reason" << std::endl;

    for(auto & i : transactions){
//        file << i.getClientOrderID() << "," << i.getOrderID() << "," << i.getInstrument() << "," << i.getSide() << ","
//            << i.getPrice() << "," << i.getQuantity() << "," << i.getStatus() << "," << i.getRejectedReason() << ","
//            << i.getTimestamp() << std::endl;
        file << i.getOrderID() << "," << i.getClientOrderID() << "," << i.getInstrument() << "," << i.getSide() << ","
             << enumValueArray[i.getStatus()] << "," << i.getQuantity() << "," << i.getPrice() << "," << i.getRejectedReason() << std::endl;
    }

    file.close();
};