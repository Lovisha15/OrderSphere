#include<bits/stdc++.h>
using namespace std;

class Order {
public:
    int serialno;
    string customer;
    int orderno;
    string contactno;
    string address;
};

vector<Order> customers;



int getInt(string prompt, int minV, int maxV) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (s.empty() || !all_of(s.begin(), s.end(), ::isdigit)) {
            cout << "Invalid input.\n";
            continue;
        }
        int val = stoi(s);
        if (val < minV || val > maxV) {
            cout << "Out of range.\n";
            continue;
        }
        return val;
    }
}

string getName() {
    string s;
    while (true) {
        cout << "Customer Name: ";
        getline(cin, s);
        if (s.size() < 2) {
            cout << "Invalid name.\n";
            continue;
        }
        return s;
    }
}

string getContact() {
    string s;
    while (true) {
        cout << "Contact (10 digits): ";
        getline(cin, s);
        if (s.size() != 10 || !all_of(s.begin(), s.end(), ::isdigit)) {
            cout << "Invalid contact.\n";
            continue;
        }
        return s;
    }
}

/* FILE HANDLING  */

void saveFile() {
    ofstream f("orders.txt");
    for (auto &p : customers) {
        f << p.serialno << "," << p.customer << "," << p.orderno << ","
          << p.contactno << "," << p.address << "\n";
    }
    f.close();
}

void loadFile() {
    customers.clear();
    ifstream f("orders.txt");
    string line;
    while (getline(f, line)) {
        stringstream ss(line);
        Order p;
        string temp;

        getline(ss, temp, ','); p.serialno = stoi(temp);
        getline(ss, p.customer, ',');
        getline(ss, temp, ','); p.orderno = stoi(temp);
        getline(ss, p.contactno, ',');
        getline(ss, p.address);

        customers.push_back(p);
    }
    f.close();
}

/*  OPERATIONS  */

void addCustomer() {
    Order p;
    p.serialno = customers.empty() ? 1 : customers.back().serialno + 1;

    cout << "Serial No: " << p.serialno << endl;
    p.customer = getName();
    p.orderno = getInt("Order No: ", 1, 999999);
    p.contactno = getContact();
    cout << "Address: ";
    getline(cin, p.address);

    customers.push_back(p);
    saveFile();
    cout << "Order added successfully!\n";
}

void viewRecords() {
    if (customers.empty()) {
        cout << "No orders found.\n";
        return;
    }

    cout << "\nSerial  Customer        OrderNo    Contact       Address\n";
    cout << string(60, '-') << endl;

    for (auto &p : customers) {
        cout << setw(6) << p.serialno
             << setw(15) << p.customer
             << setw(10) << p.orderno
             << setw(15) << p.contactno
             << p.address << endl;
    }
}

void searchOrder() {
    int id = getInt("Enter Order No to search: ", 1, 999999);
    for (auto &p : customers) {
        if (p.orderno == id) {
            cout << "\nOrder Found:\n";
            cout << "Customer: " << p.customer << "\nContact: " << p.contactno
                 << "\nAddress: " << p.address << endl;
            return;
        }
    }
    cout << "Order not found.\n";
}

void deleteRecord() {
    int id = getInt("Enter Order No to delete: ", 1, 999999);
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->orderno == id) {
            customers.erase(it);
            saveFile();
            cout << "Order deleted.\n";
            return;
        }
    }
    cout << "Order not found.\n";
}

/* - MAIN - */

int main() {
    loadFile();
    int choice;

    do {
        cout << "\n===== ORDER MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Order\n2. View Orders\n3. Delete Order\n4. Search Order\n5. Exit\n";
        choice = getInt("Choice: ", 1, 5);

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: viewRecords(); break;
            case 3: deleteRecord(); break;
            case 4: searchOrder(); break;
            case 5: cout << "Goodbye!\n";
        }
    } while (choice != 5);

    return 0;
}
