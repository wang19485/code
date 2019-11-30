#include "Store.h"
#include "Product.h"
#include "Customer.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;
Store::Store(){}
Store::Store(string name): name(name){}

string Store::getName(){ return name; }

void Store::setName(string name){
    if (name.length()==0)
        throw runtime_error("Store name cannot be empty.");
    this->name = name;
}

void Store::addProduct(int productID, string productName) {
    for (int i = 0; i < products.size(); ++i) {
        if (products.at(i).getID() == productID){
            throw runtime_error("ProductID already belongs to another product.");
        }
    }
    products.push_back(Product(productID,productName));
}

Product& Store::getProduct(int productID) {
    int count = 0;
    int mark = 0;
    for (int i = 0; i < products.size(); ++i) {
        if (products.at(i).getID() == productID) {
            ++count;
            mark = i;
        }
    }
    if (count == 0) {
        throw runtime_error("No matching product");
    }
    
    return products.at(mark);
}

void Store::addCustomer(int customerID, string customerName, bool credit) {
    for (int i = 0; i < customers.size(); ++i) {
        if (customers.at(i).getID() == customerID){
            throw runtime_error("CustomerID already belongs to another product.");
        }
    }
    //Customer customer = ;
    customers.push_back(Customer(customerID,customerName,credit));
}

Customer& Store::getCustomer(int customerID) {
    int count = 0;
    int mark = 0;
    for (int i = 0; i < customers.size(); ++i) {
        if (customers.at(i).getID() == customerID) {
            ++count;
            mark = i;
        }
    }
    if (count == 0) {
        throw runtime_error("No matching product");
    }
    return customers.at(mark);
}

void Store::takeShipment(int productID, int quantity, double cost) {
    getProduct(productID);
    getProduct(productID).addShipment(quantity, cost);
}

void Store::takePayment(int customerID, double amount) {
    getCustomer(customerID);
    getCustomer(customerID).processPayment(amount);
}

void Store::sellProduct(int customerID, int productID, int quantity) {
    getProduct(productID).reduceInventory(quantity);
    
    getCustomer(customerID).processPurchase(quantity*getProduct(productID).getPrice(), getProduct(productID));
}

string Store::listProducts() {
    ostringstream output;
        for (int i = 0; i < products.size(); ++i) {
            Product product = products.at(i);
            try {
                output << "Product Name: " << product.getName() << '\n' << "Product ID: " << product.getID() << '\n' << "Description: " << product.getDescription() << '\n' << "Inventory: " << product.getInventoryCount() << '\n' << "Number Sold: " << product.getNumberSold() << '\n' << "Total Paid: " << product.getTotalPaid() << '\n' << "Price: " << product.getPrice() << '\n' << '\n';
            }
            catch (runtime_error &e) {
            output << "Product Name: " << product.getName() << '\n' << "Product ID: " << product.getID() << '\n' << "Description: " << product.getDescription() << '\n' << "Inventory: " << product.getInventoryCount() << '\n' << "Number Sold: " << product.getNumberSold() << '\n' << "Total Paid: " << product.getTotalPaid() << '\n' << "Price: Unavailable" << '\n' << '\n';
        }
        }
    
    return output.str();
}

string Store::listCustomers() {
    ostringstream output;
    string t = "";
    for (int i = 0; i < customers.size(); ++i) {
        Customer customer = customers.at(i);
        if (customer.getCredit() == true) {
            t = "true";
        }else {
            t = "false";
        }
        output << "Customer Name: " << customer.getName() << '\n' << "Customer ID: " << customer.getID() << '\n' << "Has Credit: " << t << '\n' << "Balance: " << customer.getBalance() << '\n' << "Products Purchased --" << '\n' << '\n' <<customer.getProductsPurchased() + '\n';
    }
    return output.str();
}



