#include "Customer.h"
#include "Product.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

Customer::Customer(int customerID, const string name) : customerID(customerID), name(name), credit(false),balance(0){
    if (name.length()==0)
        throw runtime_error("Customer name cannot be empty.");
}
Customer::Customer(int customerID, const string name,bool credit) : customerID(customerID), name(name),credit(credit),balance(0){
    if (name.length()==0)
        throw runtime_error("Customer name cannot be empty.");
}
int Customer::getID() { return customerID; }

string Customer::getName() { return name; }

void Customer::setName(string name) {
    if (name.length()==0)
        throw runtime_error("Customer name cannot be empty.");
    this->name = name;
}

bool Customer::getCredit() { return credit; }

void Customer::setCredit(bool hasCredit) {
    credit = hasCredit;
}

double Customer::getBalance() { return balance; }

void Customer::processPayment(double amount) {
    if (amount < 0)
        throw runtime_error("Amount cannot be negetive.");
    balance += amount;
}
void Customer::processPurchase(double amount, Product product) {
    if (amount < 0) {
        throw runtime_error("Amount cannot be negetive.");
    }
    if (credit == true) {
        balance -= amount;
    }else {
        if (balance >= amount) {
            balance -= amount;
        }else {
            throw runtime_error("Balance cannot smaller than amount.");
        }
    }
    this->productsPurchased.push_back(product);
}
string Customer::getProductsPurchased() {
    string output ="";
    for (int i = 0; i < productsPurchased.size(); ++i) {
        output = output + "Product Name: " + productsPurchased.at(i).getName() + '\n' + "Product ID: " + to_string(productsPurchased.at(i).getID()) + '\n'+'\n';
    }
    return output;
}

ostream& operator<<(ostream &c, Customer customer) {
    string t = "";
    if (customer.getCredit() == true) {
        t = "true";
    }else {
        t = "false";
    }
    c << "Customer Name: " << customer.getName() << '\n' << "Customer ID: " << customer.getID() << '\n' << "Has Credit: " << t << '\n' << "Balance: " << customer.getBalance() << '\n' << "Products Purchased --" << '\n' << '\n' << customer.getProductsPurchased();
    return c;
}
