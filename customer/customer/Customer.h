#ifndef Customer_h
#define Customer_h
#include <string>
#include <vector>
#include "Product.h"
class Customer {
    int customerID;
    std::string name;
    bool credit;
    double balance;
    std::vector<Product>productsPurchased;
public:
    Customer( int customerID, const std::string name);
    Customer( int customerID, const std::string name,bool credit);
    int getID();
    std::string getName();
    void setName(std::string name);
    bool getCredit();
    void setCredit(bool hasCredit);
    double getBalance();
    void processPayment(double amount);
    void processPurchase(double amount,Product product);
    std::string getProductsPurchased();
}; 
std::ostream& operator<<(std::ostream &c, Customer customer);
#endif /* Customer_h */
