/*
CO SCI 536
Lab 1 
Eric Salazar
*/

#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

struct inventoryAndSize{
  item * thing;
  int size;
};

//------------------------------------------ FUNCTIONS()
//main menu for program
void display(item inventory[], int size);


//Sub menus of program
void report(item inventory[], int size);
void MenuSort(item inventory[], int size);
void search(item inventory[], int size);
void printInventory(item inventory[], int size);

//Helper Functions
int count(item inventory[], int size); //used to count number of unique items in list
void sort(item inventory[], int size, int option);

inventoryAndSize getList();//under construction
//------------------------------------------ MAIN()
// Main

int main(){
    srand (time(NULL));

    int lineCounter = 0;
    vector <item> allItems;
    stringstream temp;
    string line;
    ifstream myfile("scores.txt");
    

    //opens file myfile
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline(myfile, line))
        {
            //turn lines into object
            
            allItems.push_back(item(line));
            lineCounter++;
        }
        myfile.close();
    }
    else cout << "fooey\n";

    //reads data from file into an array
    item inventory[lineCounter];

    for (int i = 0; i < lineCounter; i++){
        inventory[i] = allItems[i];
    }

    //displays main menu for program
    display(inventory,lineCounter);
    cout << "Bye!" << endl;

  return 0;
}

//------------------------------------------ Display()
void display(item inventory[], int size){
  // Creates the menu and selectable options for the program

    char player_choice;
    bool exitProgram = false;

    do{
      cout << "MAIN-------------------" << endl;
      cout << "1) Print" << endl
          << "2) Search" << endl
          << "3) Sort" << endl
          << "4) Report" << endl
          << "5) Exit" << endl << endl;
      cout << "Please select your option:";

      cin >> player_choice; 

      cout << endl;
      switch(player_choice){

        case '1': printInventory(inventory, size);
          cout << endl;
          break;

        case '2':  search(inventory, size);
          break;

        case '3': MenuSort(inventory, size);
          break;

        case '4': report(inventory, size);
          break;

        case '5': cout << "Bye!!!" << endl;
        exitProgram = true;  
        break;

        default: cout << "Sorry, not a valid option" << endl;
          break;
        }
    }while (!exitProgram);
}


//------------------------------------------ COUNT()
//Counts unique occurences of number
int count(item inventory[], int size){

  int ret = size;
  string testArray[size];

  for (int i = 0; i < size; i++){
    testArray[i] = inventory[i].getName();
  }

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      if ((testArray[i] == testArray[j]) &&(i != j) && (testArray[j] != "")){
        testArray[j] = "";

      }
    }
  }
  
  for (int i = 0; i < size; i++){
    if (testArray[i] == ""){
      ret--;
    }
  }
  return ret;
}
  
//------------------------------------------ REPORT()
//displays the value of the inventory and number of unique items
void report(item inventory[], int size){

    double inventoryPrice = 0;
    vector <item> itemVec;
    
    for (int i = 0; i < size; i++){
        inventoryPrice += (inventory[i].getPrice() * inventory[i].getQuantity()) ;
    }
    
    cout << "Total value of inventory is: " << inventoryPrice << endl;
    
    int uniqueInts = 0;
    
    for(int i=0; i< size; i++)
    {
        itemVec.push_back(inventory[i]);
    }
    cout << "There are " << count(inventory, size) << " unique items." << endl << endl;
    
}

//----------------- MenuSORT()
void MenuSort(item inventory[], int size){
  item temp; 
  bool swap = false;
  bool exitMenu = false;
  int option;
  do{
    cout << "SORT------------" << endl;
    cout << "Please enter how you want to sort the data" << endl
        << "0) ID" << endl
        << "1) Name" << endl
        << "2) Quantity on hand" << endl
        << "3) Price" << endl
        << "4) Exit" << endl
        << "Please enter your choice: ";
    cin >> option;

    if (option == 1 || option == 0 || option == 2 || option == 3){
      exitMenu = true;
      sort(inventory, size, option);
      printInventory(inventory,size);
    }
    else if (option == 4){
      exitMenu = true;
    }
    else{
      cout << "Sorry, Invalid option." << endl;
    }
  }while(!exitMenu);
}

//----------------- SORT()
// arranges list based on option
void sort(item inventory[], int size, int option){
  item temp; 
  bool swap = false;

  //Object states:
  //ID, NAME, QUANTITY, PRICE 
  for (int i = 0; i < size - 1; i++){
    for(int j = 0; j < size - 1; j++){
      switch(option){
        case 0: swap = (inventory[j].getID() < inventory[j+1].getID());
          break;
        
        case 1: swap = (inventory[j].getName() > inventory[j+1].getName()); 
          break;
        
        case 2: swap = (inventory[j].getQuantity() < inventory[j+1].getQuantity()); 
          break;
        
        case 3: swap = (inventory[j].getPrice() < inventory[j+1].getPrice()); 
          break;
        
        default: cout << "Sorry, Invalid Option."; swap = false;
      }
      if (swap){
        temp = inventory[j];
        inventory[j] = inventory[j+1];
        inventory[j+1] = temp;
      }
    }
  }
}

//----------------- SEARCH()
//Searches for query in item.ID or item.Name
void search(item inventory[], int size){
  int playerChoice; 
  string query;
  bool notFound = true;

  cout << "SEARCH------------" << endl;
  cout << "Search by ID or Name or enter 0 to exit: ";
  cin >> query;

  if (query == "0"){
    return;
  }
  boost::to_upper(query);

  int i = 0;
  bool found=false;

  while( i < size && !found){
    found=inventory[i].getID() == query ||inventory[i].getName() == query;


    if(found)
    {
      if (inventory[i].getID() == query){
        inventory[i].print();
        cout << endl;
        return;
      }

      if(inventory[i].getName() == query){
        inventory[i].print();
        cout << endl;
        return;
      }
    }
    else
    {
      i++;
    }
  }
  cout << "Results not found" << endl << endl;
  return;
}

//----------------- PRINT INVENTORY()
// Prints array of item
void printInventory(item inventory[], int size){
    cout << "PRINT------------" << endl;
    cout << "INVENTORY: " << endl;
    for (int i = 0; i < size; i++){
    inventory[i].print();
  }
}

/*
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:1

PRINT------------
INVENTORY:
 2204    BANANA  25   71.46
 9403     SHOES  52    83.8
 5517     COUCH  35    43.4
 1075      SOUP  42   34.56
 6442      BOOK  78    77.7
 2534    PLANET   3   36.62
 5118      KVAS   0    17.4
 5267   SMETANA  54   34.01
 6337   PIEROGI  56   48.74
 2906    TARHUN   2    8.06
 2534    PLANET   2   36.62
 1235  COMPUTER   3   45.32

MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:2

SEARCH------------
Search by ID or Name or enter 0 to exit: kvas
 5118      KVAS   0    17.4

MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:2

SEARCH------------
Search by ID or Name or enter 0 to exit: 2534
 2534    PLANET   3   36.62

MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:2

SEARCH------------
Search by ID or Name or enter 0 to exit: 0
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:3

SORT------------
Please enter how you want to sort the data
0) ID
1) Name
2) Quantity on hand
3) Price
4) Exit
Please enter your choice: 0
PRINT------------
INVENTORY:
 9403     SHOES  52    83.8
 6442      BOOK  78    77.7
 6337   PIEROGI  56   48.74
 5517     COUCH  35    43.4
 5267   SMETANA  54   34.01
 5118      KVAS   0    17.4
 2906    TARHUN   2    8.06
 2534    PLANET   3   36.62
 2534    PLANET   2   36.62
 2204    BANANA  25   71.46
 1235  COMPUTER   3   45.32
 1075      SOUP  42   34.56
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:3

SORT------------
Please enter how you want to sort the data
0) ID
1) Name
2) Quantity on hand
3) Price
4) Exit
Please enter your choice: 1
PRINT------------
INVENTORY:
 2204    BANANA  25   71.46
 6442      BOOK  78    77.7
 1235  COMPUTER   3   45.32
 5517     COUCH  35    43.4
 5118      KVAS   0    17.4
 6337   PIEROGI  56   48.74
 2534    PLANET   3   36.62
 2534    PLANET   2   36.62
 9403     SHOES  52    83.8
 5267   SMETANA  54   34.01
 1075      SOUP  42   34.56
 2906    TARHUN   2    8.06
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:3

SORT------------
Please enter how you want to sort the data
0) ID
1) Name
2) Quantity on hand
3) Price
4) Exit
Please enter your choice: 2
PRINT------------
INVENTORY:
 6442      BOOK  78    77.7
 6337   PIEROGI  56   48.74
 5267   SMETANA  54   34.01
 9403     SHOES  52    83.8
 1075      SOUP  42   34.56
 5517     COUCH  35    43.4
 2204    BANANA  25   71.46
 1235  COMPUTER   3   45.32
 2534    PLANET   3   36.62
 2534    PLANET   2   36.62
 2906    TARHUN   2    8.06
 5118      KVAS   0    17.4
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:3

SORT------------
Please enter how you want to sort the data
0) ID
1) Name
2) Quantity on hand
3) Price
4) Exit
Please enter your choice: 3
PRINT------------
INVENTORY:
 9403     SHOES  52    83.8
 6442      BOOK  78    77.7
 2204    BANANA  25   71.46
 6337   PIEROGI  56   48.74
 1235  COMPUTER   3   45.32
 5517     COUCH  35    43.4
 2534    PLANET   3   36.62
 2534    PLANET   2   36.62
 1075      SOUP  42   34.56
 5267   SMETANA  54   34.01
 5118      KVAS   0    17.4
 2906    TARHUN   2    8.06
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:3

SORT------------
Please enter how you want to sort the data
0) ID
1) Name
2) Quantity on hand
3) Price
4) Exit
Please enter your choice: 4
MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:4

Total value of inventory is: 20076.4
There are 11 unique items.

MAIN-------------------
1) Print
2) Search
3) Sort
4) Report
5) Exit

Please select your option:5

Bye!!!
Bye!





*/