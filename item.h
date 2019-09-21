#ifndef item_H
#define item_H


#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>
 
using namespace std;

class item{
    //STATES:
    //ID NAME QUANTITY PRICE
    string ID;
    string name;
    int quantity;
    double price;

    //METHODS
    public:
        //INTIALIZER / DESTRUCTOR
        item();
        item(string inventoryInfo);
    
        //MISC METHODS
        void print();

        //GETTERS
        string getID(){return ID;};
        string getName(){return name;};
        int getQuantity(){return quantity;};
        double getPrice(){return price;};

        //OVERLOADED OPERATORS
        item& operator=(item x){ this->ID = x.getID(); this-> name = x.getName(); this->quantity = x.getQuantity(); this->price = x.getPrice(); return *this;};

};

#endif //item_H
