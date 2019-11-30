#include "Product.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

Product::Product(int id, string name) : id(id), name(name),
inventory(0), numSold(0), totalPaid(0.0) /*, description("")*/ {
    if (name.length()==0)
        throw runtime_error("Product name cannot be empty.");
}
int Product::getID() { return id; }

string Product::getName() { return name; }

void Product::setName(string name) {
    if (name.length()==0)
        throw runtime_error("Product name cannot be empty.");
    this->name = name;
}

string Product::getDescription() { return description; }

void Product::setDescription(string description){
    this->description = description;
}

int Product::getNumberSold() { return numSold; }

double Product::getTotalPaid() { return totalPaid; }

int Product::getInventoryCount() { return inventory; }

double Product::getPrice() {
    if (inventory == 0) {
        throw runtime_error("No inventory.");
    }
    double price =  (totalPaid / (inventory + numSold)) * 1.25;
    return price;
}

void Product::addShipment(int quantity, double shipmentCost) {
    if (quantity < 0)
        throw runtime_error("Shipment quantity must be positive.");
    if (shipmentCost < 0)
        throw runtime_error("Shipment cost must be positive.");
    inventory += quantity;
    totalPaid += shipmentCost;
}

void Product::reduceInventory(int quantity) {
    if (inventory < quantity)
        throw runtime_error("Not enough inventory.");
    if (quantity < 0)
        throw runtime_error("Purchase Quantity cannot be negetive.");
    inventory -= quantity;
    numSold += quantity;
}

ostream& operator<<(ostream &pp, Product product) {
    pp << "Product Name: " << product.getName() << '\n' << "Product ID: " << product.getID() << '\n' << "Description: " << product.getDescription() << '\n' << "Inventory: " << product.getInventoryCount() << '\n' << "Number Sold: " << product.getNumberSold() << '\n' << "Total Paid: " << product.getTotalPaid() << '\n' << "Price: " << product.getPrice() << '\n';
    return pp;
}
