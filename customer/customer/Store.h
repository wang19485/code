#ifndef Store_h
#define Store_h
#include <string>
#include <vector>
#include "Product.h"
#include "Customer.h"

class Store {
    std::string name;
    std::vector<Product>products;
    std::vector<Customer>customers;
public:
    Store();
    Store(std::string name);
    std::string getName();
    void setName(std::string name);
    void addProduct(int productID, std::string productName);
    Product& getProduct(int productID);
    void addCustomer(int customerID, std::string customerName, bool credit=false);
    Customer& getCustomer(int customerID);
    void takeShipment(int productID, int quantity, double cost);
    void takePayment(int customerID, double amount);
    void sellProduct(int customerID, int productID, int quantity);
    std::string listProducts();
    std::string listCustomers();
};
std::ostream& operator<<(std::ostream &p, Product product);
std::ostream& operator<<(std::ostream &c, Customer customer);
#endif /* Store_h */
