#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

class student {
public:
    long int reg;
    char name[80], branch[50];

    void input() {
        cin.ignore();
        cout << "\nEnter name: ";
        cin.getline(name, 80);
        cout << "\nEnter reg no: ";
        cin >> reg;
        cin.ignore();
        cout << "\nEnter branch: ";
        cin.getline(branch, 50);
    }

    void display() {
        cout << "\n-------------------------------------";
        cout << "\nName    : " << name;
        cout << "\nReg no. : " << reg;
        cout << "\nBranch  : " << branch;
        cout << "\n-------------------------------------\n";
    }

    bool operator==(student a) {
        return reg == a.reg;
    }
};

vector<student> v;

void get_file() {
    student x;
    ifstream f("College.txt", ios::in | ios::binary);
    if (f) {
        while (f.read((char*)&x, sizeof(student))) {
            v.push_back(x);
        }
    } else {
        cout << "\nNo existing data file found. Starting fresh.\n";
    }
    f.close();
}

void write_file() {
    ofstream f("College.txt", ios::out | ios::binary);
    for (const auto& x : v) {
        f.write((char*)&x, sizeof(student));
    }
    f.close();
}

void bubblesort() {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = 0; j < v.size() - i - 1; j++) {
            if (v[j].reg > v[j + 1].reg) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

int search_reg(long int reg, int& i) {
    for (i = 0; i < v.size(); i++) {
        if (v[i].reg == reg) {
            return 1;
        }
    }
    return 0;
}

void insert_new() {
    char ch = 'y';
    while (ch == 'y' || ch == 'Y') {
        student x;
        x.input();
        int idx;
        if (search_reg(x.reg, idx) == 0) {
            v.push_back(x);
        } else {
            cout << "\nThe registration number already exists! Cannot add.\n";
        }
        cout << "\nPress [Y] to enter more: ";
        cin >> ch;
    }
}

void show() {
    if (v.empty()) {
        cout << "\nNo records to display!\n";
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        cout << "\nRecord " << i + 1 << ":";
        v[i].display();
    }
}

void delete_data() {
    long int reg;
    cout << "\nEnter reg no: ";
    cin >> reg;
    int idx;
    if (search_reg(reg, idx) == 1) {
        cout << "\nThe following data is being deleted:";
        v[idx].display();
        v.erase(v.begin() + idx);
        cout << "\nRecord deleted successfully.\n";
    } else {
        cout << "\nRecord not found!\n";
    }
}

void edit_data() {
    long int reg;
    cout << "\nEnter reg no: ";
    cin >> reg;
    int idx;
    if (search_reg(reg, idx) == 1) {
        cout << "\nEnter new data:\n";
        v[idx].input();
    } else {
        cout << "\nRecord not found!\n";
    }
}

void search_and_show() {
    int choice, idx;
    long int reg;
    char name[80], branch[50];
    vector<int> results;

    cout << "\n1. Search by Reg no.";
    cout << "\n2. Search by Name";
    cout << "\n3. Search by Branch";
    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "\nEnter reg no: ";
        cin >> reg;
        if (search_reg(reg, idx)) {
            v[idx].display();
        } else {
            cout << "\nRecord not found!\n";
        }
        break;
    case 2:
        cin.ignore();
        cout << "\nEnter name: ";
        cin.getline(name, 80);
        for (int i = 0; i < v.size(); i++) {
            if (strcmp(v[i].name, name) == 0) {
                results.push_back(i);
            }
        }
        if (results.empty()) {
            cout << "\nRecord not found!\n";
        } else {
            for (int idx : results) {
                v[idx].display();
            }
        }
        break;
    case 3:
        cin.ignore();
        cout << "\nEnter branch: ";
        cin.getline(branch, 50);
        for (int i = 0; i < v.size(); i++) {
            if (strcmp(v[i].branch, branch) == 0) {
                results.push_back(i);
            }
        }
        if (results.empty()) {
            cout << "\nRecord not found!\n";
        } else {
            for (int idx : results) {
                v[idx].display();
            }
        }
        break;
    default:
        cout << "\nInvalid choice!\n";
    }
}

int main() {
    get_file();
    int choice;

    while (true) {
        #ifdef _WIN32
            system("CLS");
        #else
            system("clear");
        #endif

        cout << "\n-----------------------------------------";
        cout << "\n   Simple College Management System";
        cout << "\n-----------------------------------------";
        cout << "\n1. Add new student";
        cout << "\n2. Display all students";
        cout << "\n3. Remove student";
        cout << "\n4. Edit student";
        cout << "\n5. Search student";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            insert_new();
            break;
        case 2:
            show();
            break;
        case 3:
            delete_data();
            break;
        case 4:
            edit_data();
            break;
        case 5:
            search_and_show();
            break;
        case 0:
            write_file();
            cout << "\nExiting the program. Data saved to file.";
            return 0;
        default:
            cout << "\nInvalid choice! Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
