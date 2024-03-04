#include <iostream>
#include <string>
#include <vector>
#include<conio.h>
#include<fstream>
#include<sstream>
using namespace std;
class customerVendor {
public:
    string customer_name;
    int customer_id;
    int customer_phone_number;
    int customer_address;
    string Vendors;
    int Vendor_phone_number;

    string getcustomername() {
        return customer_name;
    }
    int getcustomer_id() {
        return customer_id;
    }
    int getcustomerphone() {
        return customer_phone_number;
    }
    int getcustomer_address() {
        return customer_address;
    }
    string getvendor() {
        return Vendors;
    }
    int getvendorphone() {
        return Vendor_phone_number;
    }


};

// Item class to represent a medication in the inventory
class Item {
private:
    string itemName;
    int Quantity;
    double Price;
    string expirydate;
    string type_of_item;

public:
    Item(string name, string typeitem, int quantity, string exp, double price) {
        this->itemName = name;
        this->Quantity = quantity;
        this->Price = price;
        this->expirydate = exp;
        this->type_of_item = typeitem;
    }
    string getitemName() {
        return itemName;
    }
    string gettypeofitem() {
        return type_of_item;
    }
    int getQuantity() {
        return Quantity;
    }
    double getPrice() {
        return Price;
    }
    string getexpirydate() {
        return expirydate;
    }
    void setQuantity(int quantity) {
        this->Quantity = quantity;
    }
    void settexpirydate() {
        this->expirydate = expirydate;
    }
};

// PharmacyInventory class to manage the inventory of the pharmacy
class PharmacyInventory {
private:
    vector<Item>items;
public:
    void addItem(string name, string type, int quantity, string expiryDate, double price) {
        items.push_back(Item(name, type, quantity, expiryDate, price));
    }
    // Item removes when you enter the name of item 
    void removeItem(string name) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getitemName() == name) {
                items.erase(items.begin() + i);
                break;
            }
        }
    }
    // items display with their name,quantity and price
    void displayInventory() {
        cout << "Pharmacy Inventory:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << "Item " << i + 1 << ":" << endl;
            cout << "Name: " << items[i].getitemName() << endl;
            cout << "Quantity: " << items[i].getQuantity() << endl;
            cout << "Price: $" << items[i].getPrice() << endl;
        }
    }
    // selling item by getting name and quantity
    void sellItem(string name, int quantity) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i].getitemName() == name) {
                int newQuantity = items[i].getQuantity() - quantity;
                if (newQuantity < 0) {
                    cout << "Insufficient quantity!" << endl;
                    return;
                }
                items[i].setQuantity(newQuantity);

                if (newQuantity < 15) {
                    callVendor(name, newQuantity);
                }

                cout << "Sold " << quantity << " " << name << "(s)." << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }
    // if quantity is less than 15 call the vendor
    void callVendor(string name, int quantity) {
        cout << "Calling vendor for item " << name << ". Current quantity: " << quantity << endl;
        // Add code to call the vendor here
    }
    //saving file at csv inventory
    void opencsv(string inputfile) {
        ofstream file(inputfile);
        if (!file.is_open()) {
            cout << "Failed to open the CSV file for writing." << endl;
            return;
        }
        // run automatically if file is fail for writing
        for (auto& item : items) {
            file << item.getitemName() << "," << item.getQuantity() << "," << item.getPrice() << endl;
        }
        // file close if input is ssuccessful
        file.close();
        cout << "Inventory saved to " << inputfile << " successfully." << endl;
    }
    //read file at csv  inventory
    void readcsv(string inputfile) {
        ifstream file(inputfile);
        if (!file.is_open()) {
            cout << "Failed to open the CSV file for reading." << endl;
            return;
        }
        //if fail to open all items are listed zero
        items.clear();


        string line;
        getline(file, line);
        // used getline for too many string values
        while (getline(file, line)) {
            stringstream obj(line);
            string customerName;
            string customerID;
            string customerPhone;
            string customerAddress;
            string itemName;
            string type;
            int quantity;
            string expiryDate;
            double price;
            getline(obj, customerName, ',');
            getline(obj, customerID, ',');
            getline(obj, customerPhone, ',');
            getline(obj, customerAddress, ',');
            getline(obj, itemName, ',');
            getline(obj, type, ',');
            obj >> quantity;
            
            getline(obj, expiryDate, ',');
            obj >> price;

            // Add the item to the inventory
            items.push_back(Item(itemName, type, quantity,  expiryDate, price));
        }

        file.close();
        cout << "Inventory loaded from " << inputfile << " successfully." << endl;
    }

    // as file read successfully it will be open
};

// functions are passed  to get  to the main
int main() {
    PharmacyInventory inventory;
    int choice;
    //username and password are fixed initially
    string username = "admin";
    string password = "password";
    string inputUsername;
    string inputPassword;

    cout << "Enter your Username: ";
    cin >> inputUsername;

    cout << "Enter your Password: ";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!inputPassword.empty()) {
                cout << "\b \b";
                //getch used to convert char to int
            }
        }
        else {
            cout << '*';
            inputPassword += ch;
        }
    }

    cout << endl;

    if (inputUsername == username && inputPassword == password) {
        cout << "-------Login successful! Welcome, " << username << "-------" << endl;
        //if login success full file will read


        inventory.readcsv("pharmacydata.csv");
        do {
            cout << "------Pharmacy Inventory Management System------" << endl;
            cout << "1. Add Item" << endl;
            cout << "2. Remove Item" << endl;
            cout << "3. Display Inventory" << endl;
            cout << "4. Sell Item" << endl;
            cout << "5. Quit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                // in case 1 items add using all argument to add
            case 1: {
                string name;
                string type; 
                int quantity;
                string expiryDate; 
                double price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item type: ";
                cin >> type;
                cout << "Enter item quantity: ";
                cin >> quantity;
                cout << "Enter item expiry date: ";
                cin >> expiryDate;
                cout << "Enter item price: ";
                cin >> price;
                inventory.addItem(name, type, quantity, expiryDate, price);
                break;
            }
                  // remove item only need acess of name
            case 2: {
                string name;
                cout << "Enter item name: ";
                cin >> name;
                inventory.removeItem(name);
                break;
            }
                  // display will display all data related to item
            case 3: {
                inventory.displayInventory();
                break;
            }
                  //case 4 will ask for item name and quantity
            case 4: {
                string name;
                int quantity;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter item quantity: ";
                cin >> quantity;
                inventory.sellItem(name, quantity);
                break;
            }
                  // for exit use case 5
            case 5: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice!" << endl;
            }
            }
            //while is also use for exit
        } while (choice != 5);


    }

    else {
        cout << "Invalid Username or Password. Login Failed." << endl;


    }

    return 0;
}
