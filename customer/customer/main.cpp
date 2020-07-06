#include <iostream>
#include "Product.h"
#include "Customer.h"
#include "Store.h"
using namespace std;
int main() {
    try {
        Product p(17, "Jill");
        cout << "p (id): " << p.getID() << endl;
        cout << "p (name): " << p.getName() << endl;
        
        //Product q(183, "Tom");
        //cout << "q (id): " << q.getID() << endl;
        //cout << "q (name): " << q.getName() << endl;
        
        //Product badP(222, "");
        //cout << "badP (id): " << badP.getID() << endl;
        //cout << "badP (name): " << badP.getName() << endl;
        
        //p.setName("Jill Extreme");
        //cout << "p (name): " << p.getName() << endl;
        
        //q.setName("");
        //cout << "q (name): " << q.getName() << endl;
        
        cout << "Before 1st shipment" << endl;
        cout << "inventory: " << p.getInventoryCount() << endl;
        cout << "totalPaid: " << p.getTotalPaid() << endl;
        
        p.addShipment(88, 230.44);
        
        cout << "After 1st shipment" << endl;
        cout << "inventory: " << p.getInventoryCount() << endl;
        cout << "totalPaid: " << p.getTotalPaid() << endl;
        
        p.addShipment(133, 142.11);
        
        cout << "After 2nd shipment" << endl;
        cout << "inventory: " << p.getInventoryCount() << endl;
        cout << "totalPaid: " << p.getTotalPaid() << endl;
        
        //cout << "Testing negative quantity" << endl;
        
        p.addShipment(-5, 22.55);
        
        //cout << "Testing negative shipment cost" << endl;
        
        p.addShipment(5, -22.55);
        cout << "Price: " << p.getPrice() << endl;
    }
    catch (runtime_error& exc) {
        cout << "Exception caught: "<< exc.what() << endl;
    }
    
    try {
    Product p(32498,"gg");
    cout << "Product Name: " << p.getName() << endl;
    cout << "Product ID: " << p.getID() << endl;
    
    p.setDescription("A great way to keep a canned beverage cold.");
    cout << "Description: " << p.getDescription() << endl;
    
    p.addShipment(108, 2850);
    p.reduceInventory(107);
    cout << "Inventory: " << p.getInventoryCount() << endl;
    cout << "Number Sold: " << p.getNumberSold() << endl;
    cout << "Total Paid: " << p.getTotalPaid() << endl;
    cout << "Price: " << p.getPrice() << endl;
    }
    catch (runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
   Customer c1(987,"Ms Jackson",true);
    cout << c1.getCredit();
}
