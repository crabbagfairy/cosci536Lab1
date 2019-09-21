#include "item.h"
#include <iomanip>

using namespace std;

//-------------------ITEM()
item::item()
//default constructor which creates random objects
{
  string tempName = "";
  char tempChar;
  int tempInt;
  double tempDouble; 

  for (int i=0; i< 3; i++)
    {    tempInt = rand() % 26;   // generate a random number
          tempChar = 'a' + tempInt;            // Convert to a character from a-z
          tempName += tempChar;
    }

  int quark = (rand() % 10000) + 1000;
  ID = to_string(quark);

  name = tempName; 
  quantity = rand() % 100 ;

  tempDouble = rand() % 100; 
  tempDouble /= 100;

  price = (rand() % 100) + tempDouble ; 
}

//-------------------~ITEM(STRINGSTREAM)
//constructor that reads in file
item::item(string inventoryInfo){
    
    stringstream temp;
    string tempID;
    string tempName;
    int tempQuantity;
    double tempPrice;
    
    temp << inventoryInfo;
    
    temp >> tempID >> tempName >> tempQuantity >> tempPrice;

    ID = tempID;
    
    //transform(tempName.begin(), tempName.end(), tempName.begin(), ::toupper);
    boost::to_upper(tempName);
    name = tempName;
    quantity = tempQuantity;
    price = tempPrice;
    
}

//-------------------ITEM.PRINT()
void item::print(){
  cout << setw(5) << ID << setw(10) << name << setw(4) << quantity << setw(8) << price << endl;
}


